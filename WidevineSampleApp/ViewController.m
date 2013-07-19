//
//  ViewController.m
//  WidevineExample
//
//  Created by David McGaffin on 9/6/12.
//
//

#import "BCQueuePlayer.h"
#import "BCVideo.h"
#import "BCCatalog.h"
#import "BCEventLogger.h"
#import "BCUIControls.h"
#import "BCPlaylist.h"
#import "BCEvent.h"
#import "BCWidevinePlugin.h"
#import "Constants.h"

#import "WidevineInfo.h"
#import "ViewController.h"

@interface ViewController ()
{
    BCWidevinePlugin *widevinePlugin;
    BCQueuePlayer *player;
    BCCatalog *catalog;
    BCEventEmitter *eventEmitter;
    BCEventLogger *logger;
    BCUIControls *controlsComponent;
    WidevineInfo *infoComponent;
}

@property(nonatomic,strong) BCWidevinePlugin *widevinePlugin;
@property(nonatomic,strong) BCQueuePlayer *player;
@property(nonatomic,strong) BCCatalog *catalog;
@property(nonatomic,strong) BCEventEmitter *eventEmitter;
@property(nonatomic,strong) BCEventLogger *logger;
@property(nonatomic,strong) BCUIControls *controlsComponent;
@property(nonatomic,strong) WidevineInfo *infoComponent;
@end

@implementation ViewController

@synthesize widevinePlugin;
@synthesize player;
@synthesize catalog;
@synthesize eventEmitter;
@synthesize logger;
@synthesize controlsComponent;
@synthesize infoComponent;

- (void)dealloc
{
    
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    NSString *path = [[NSBundle mainBundle] pathForResource:@"widevine" ofType:@"plist"];
    NSDictionary *dictionary = [NSDictionary dictionaryWithContentsOfFile:path];
    
    // To test with a different base url for the media api, add a string value to 'widevine.plist' named
    // 'mediaApiBaseUrl' with the value set to the base url you would like to test.
    [self initializePluginWithToken:(NSString *) [dictionary objectForKey:@"mediaApiToken"]
                            baseUrl:[dictionary objectForKey:@"mediaApiBaseUrl"]];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(refreshPlaylist)
                                                 name:BCWidevinePluginRefreshPlaylist
                                               object:nil];
    [self refreshPlaylist];
}

- (void)refreshPlaylist
{
    NSString *path = [[NSBundle mainBundle] pathForResource:@"widevine" ofType:@"plist"];
    NSDictionary *dictionary = [NSDictionary dictionaryWithContentsOfFile:path];
    
    [self.widevinePlugin stop];
    
    __weak ViewController *weakself = self;
    [widevinePlugin findPlaylistByReferenceID:[dictionary objectForKey:@"iosPlaylistReferenceId"]
                                      options:nil
                                    callBlock:^(BCError *error, BCPlaylist *playlist) {
                                        
                                        if (playlist) {
                                            if (!self.infoComponent) {
                                                [weakself createInfoView];
                                            }
                                            BCVideo *firstVideo = [playlist.videos objectAtIndex:0];
                                            [widevinePlugin queueVideo:firstVideo];
                                            
                                            [[NSNotificationCenter defaultCenter] postNotification:
                                             [NSNotification notificationWithName:BCWidevinePluginDidRefreshPlaylist object:self]];
                                        } else if (error) {
                                            [weakself displayErrorAlert:error.description];
                                        }
                                    }];
}

- (void)initializePluginWithToken:(NSString *)token baseUrl:(NSString *)baseUrl
{
    self.widevinePlugin = [[BCWidevinePlugin alloc] initWithToken:token baseURL:baseUrl];
    self.player = self.widevinePlugin.player;
    
    [self.view addSubview:self.player.view];
    self.eventEmitter = self.player.playbackEmitter;

    // enable logging.
    [self.eventEmitter emit:BCEventSetDebug withDetails:[NSDictionary dictionaryWithObject:[NSNumber numberWithBool:YES]
                                                                               forKey:@"debug"]];
    self.logger = [[BCEventLogger alloc] initWithEventEmitter:self.eventEmitter];
    [self.logger setVerbose:NO];
    
    // First video will not auto-play, but subsequent videos will.
    __weak ViewController *weakself = self;
    [self.eventEmitter once:BCEventVideoDidEnd callBlock:^(BCEvent *event) {
        weakself.widevinePlugin.autoPlay = YES;
    }];
    
    [self.eventEmitter on:BCEventDidSetVideo callBlock:^(BCEvent *event) {
        [[NSNotificationCenter defaultCenter] postNotification:
         [NSNotification notificationWithName:BCWidevinePluginDidSetVideo object:self userInfo:event.details]];
    }];

    UIView *controlsView = [[UIView alloc] initWithFrame:CGRectMake(0, 180, 320, 50)];
    [self.view addSubview:controlsView];
    self.controlsComponent = [[BCUIControls alloc] initWithEventEmitter:self.eventEmitter andView:controlsView];
}

- (BOOL)shouldAutorotate
{
    return NO;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        return (interfaceOrientation == UIInterfaceOrientationPortrait);
    } else {
        return NO;
    }
}

#pragma mark - BC iOS Integration

- (void)displayErrorAlert:(NSString *)message
{
    NSLog(@"ERROR: %@", message);
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"Error"
                                                    message:message
                                                   delegate:nil
                                          cancelButtonTitle:@"ok"
                                          otherButtonTitles:nil];
    [alert show];
}

- (void)createInfoView
{
    UIView *infoView = [[UIView alloc] initWithFrame:CGRectMake(0, 230, 320, 250)];
    [self.view addSubview:infoView];
    
    self.infoComponent = [[WidevineInfo alloc] initWithEventEmitter:self.eventEmitter
                                                             plugin:self.widevinePlugin];
    [infoView addSubview:self.infoComponent.widevineInfoView];
}

@end
