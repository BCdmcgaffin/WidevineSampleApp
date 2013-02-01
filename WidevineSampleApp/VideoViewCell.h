//
//  VideoViewCell.h
//  WidevinePlugin
//
//  Created by David McGaffin on 1/25/13.
//
//

#import <UIKit/UIKit.h>

@interface VideoViewCell : UITableViewCell

+ (NSString *)reuseIdentifier;

@property(strong,nonatomic) IBOutlet UIImageView *videoStill;
@property(strong,nonatomic) IBOutlet UILabel *videoNameLabel;
@property(strong,nonatomic) IBOutlet UILabel *durationLabel;
@end
