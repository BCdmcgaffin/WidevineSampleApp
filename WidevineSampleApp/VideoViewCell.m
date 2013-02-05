//
//  VideoViewCell.m
//  WidevinePlugin
//
//  Created by David McGaffin on 1/25/13.
//
//

#import "VideoViewCell.h"

@implementation VideoViewCell

@synthesize videoStill;
@synthesize videoNameLabel;
@synthesize durationLabel;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
    UIView *bgColorView = [[UIView alloc] init];
    [bgColorView setBackgroundColor:[UIColor colorWithRed:0.016 green:0.333 blue:0.569 alpha:1]]; /*#045591*/
    [self setSelectedBackgroundView:bgColorView];
    [bgColorView release];
}

+ (NSString *)reuseIdentifier {
    return @"VideoViewCellIdentifier";
}

@end
