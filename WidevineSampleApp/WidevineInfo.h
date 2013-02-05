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

@property(nonatomic,retain) IBOutlet UIView *widevineInfoView;

@property(nonatomic, retain) BCWidevinePlugin *widevinePlugin;

@property(assign,nonatomic) IBOutlet VideoViewCell *videoCell;

@property(strong,nonatomic) IBOutlet UITableView *tableView;

@end
