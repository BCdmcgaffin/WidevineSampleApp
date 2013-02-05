//
//  WidevineInfo.m
//  WidevinePlugin
//
//  Created by David McGaffin on 9/26/12.
//
//

#import "WViPhoneAPI.h"
#import "BCVideo.h"
#import "BCEvent.h"
#import "BCWidevinePlugin.h"
#import "UIScrollView+SVPullToRefresh.h"
#import "Constants.h"

#import "WidevineInfo.h"

@implementation WidevineInfo

@synthesize widevinePlugin;
@synthesize widevineInfoView;
@synthesize videoCell = _videoCell;
@synthesize tableView = _tableView;

- (id)init
{
    [super dealloc];
    return nil;
}

- (id)initWithEventEmitter:(BCEventEmitter *)eventEmitter
                    plugin:(BCWidevinePlugin *)plugin
{
    if (self = [super initWithEventEmitter:eventEmitter]) {
        [[NSBundle mainBundle] loadNibNamed:@"WidevineInfo_iphone" owner:self options:nil];
        
        self.widevinePlugin = plugin;
        
        [self.tableView addPullToRefreshWithActionHandler:^{
            [[NSNotificationCenter defaultCenter] postNotification:[NSNotification notificationWithName:BCWidevinePluginRefreshPlaylist
                                                                                                 object:self]];
            self.widevinePlugin.autoPlay = NO;
            [self.tableView.pullToRefreshView stopAnimating];
        }];
        
        NSNotificationCenter *nc = [NSNotificationCenter defaultCenter];
        [nc addObserver:self selector:@selector(reloadPlaylist) name:BCWidevinePluginDidRefreshPlaylist object:nil];
        [nc addObserver:self selector:@selector(selectVideo:) name:BCWidevinePluginDidSetVideo object:nil];
    }
    
    return self;
}

- (void)dealloc
{
    self.widevineInfoView = nil;
    self.widevinePlugin = nil;
    
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    
    [super dealloc];
}

- (void)reloadPlaylist
{
    [self.tableView reloadData];
    [self.tableView.pullToRefreshView stopAnimating];
    
    [self.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0]
                                animated:YES
                          scrollPosition:UITableViewScrollPositionTop];
}

- (void)selectVideo:(NSNotification *)notification
{
    BCVideo *video = [notification.userInfo objectForKey:@"video"];
    NSUInteger row = [self.widevinePlugin.playlist.videos indexOfObject:video];
    [self.tableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:row inSection:0]
                                animated:YES
                          scrollPosition:UITableViewScrollPositionMiddle];
}

#pragma mark - UITableView Delegate

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [self.widevinePlugin.playlist.videos count];
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 80;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	// Try to retrieve from the table view a now-unused cell with the given identifier.
	VideoViewCell *cell = (VideoViewCell *)[tableView dequeueReusableCellWithIdentifier:[VideoViewCell reuseIdentifier]];
	
	// If no cell is available, create a new one using the given identifier.
	if (cell == nil) {
        [[NSBundle mainBundle] loadNibNamed:@"VideoViewCell" owner:self options:nil];
        cell = _videoCell;
        _videoCell = nil;
	}
	
	// Set up the cell.
	BCVideo *video = [self.widevinePlugin.playlist.videos objectAtIndex:indexPath.row];
    NSURL *stillUrl = [video.properties objectForKey:@"videoStillURL"];
    NSData *imageData = [NSData dataWithContentsOfURL:stillUrl];
    cell.videoStill.image = [UIImage imageWithData:imageData];
	cell.videoNameLabel.text = [video.properties objectForKey:@"name"];
    cell.durationLabel.text = [self hmsForDuration:[video.properties objectForKey:@"duration"]];
	
	return cell;
}

- (NSString *)hmsForDuration:(NSNumber *)duration
{
    unsigned long seconds = duration.unsignedLongValue / 1000;
    NSUInteger h = seconds / 3600;
    NSUInteger m = (seconds / 60) % 60;
    NSUInteger s = (seconds % 60);
    
    return [NSString stringWithFormat:@"%u:%02u:%02u", h, m, s];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    BCVideo *video = [self.widevinePlugin.playlist.videos objectAtIndex:indexPath.row];
    
    self.widevinePlugin.autoPlay = YES;
    [self.widevinePlugin queueVideo:video];
}

@end
