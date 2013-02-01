//
//  MPVolumeView.h
//  MediaPlayer
//
//  Copyright 2008-2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <MediaPlayer/MediaPlayerDefines.h>

MP_EXTERN_CLASS_AVAILABLE(2_0) @interface MPVolumeView : UIView <NSCoding>

- (CGSize)sizeThatFits:(CGSize)size;

@property (nonatomic) BOOL showsVolumeSlider NS_AVAILABLE_IOS(4_2); // Default is YES.
@property (nonatomic) BOOL showsRouteButton NS_AVAILABLE_IOS(4_2);  // Default is YES.

// Volume slider customization

- (void)setMinimumVolumeSliderImage:(UIImage *)image forState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (void)setMaximumVolumeSliderImage:(UIImage *)image forState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (void)setVolumeThumbImage:(UIImage *)image forState:(UIControlState)state NS_AVAILABLE_IOS(6_0);

- (UIImage *)minimumVolumeSliderImageForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (UIImage *)maximumVolumeSliderImageForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (UIImage *)volumeThumbImageForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);

- (CGRect)volumeSliderRectForBounds:(CGRect)bounds NS_AVAILABLE_IOS(6_0);
- (CGRect)volumeThumbRectForBounds:(CGRect)bounds volumeSliderRect:(CGRect)rect value:(float)value NS_AVAILABLE_IOS(6_0);

// Route button customization

- (void)setRouteButtonImage:(UIImage *)image forState:(UIControlState)state NS_AVAILABLE_IOS(6_0);
- (UIImage *)routeButtonImageForState:(UIControlState)state NS_AVAILABLE_IOS(6_0);

- (CGRect)routeButtonRectForBounds:(CGRect)bounds NS_AVAILABLE_IOS(6_0);

@end
