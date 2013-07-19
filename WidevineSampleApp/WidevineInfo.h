//
//  WidevineInfo.h
//  WidevinePlugin
//
//  Created by David McGaffin on 9/26/12.
#import "BCComponent.h"
#import "BCEventEmitter.h"
#import "BCQueuePlayer.h"
#import "VideoViewCell.h"

@interface WidevineInfo : BCComponent<UIScrollViewDelegate,UITableViewDelegate,UITableViewDataSource>
{
    UIView *widevineInfoView;
    BCWidevinePlugin *widevinePlugin;
}

- (id)initWithEventEmitter:(BCEventEmitter *)eventEmitter plugin:(BCWidevinePlugin *) widevinePlugin;

@property(nonatomic,strong) IBOutlet UIView *widevineInfoView;

@property(nonatomic, strong) BCWidevinePlugin *widevinePlugin;

@property(weak,nonatomic) IBOutlet VideoViewCell *videoCell;

@property(strong,nonatomic) IBOutlet UITableView *tableView;

@end
