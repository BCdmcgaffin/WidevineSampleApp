//
//  BCPlayerItem.h
//  BCiOSSDK
//
//  Created by Tom Ruggles on 8/7/12.
//
//

#import <Foundation/Foundation.h>
@class AVPlayerItem;
@class BCVideo;

@interface BCPlayerItem : NSObject

///---------------------------------------------------------------------------------------
/// @name Creating an Item
///---------------------------------------------------------------------------------------

/**
 * Designated initializer, constructs a new BCPlayerItem with the given player
 * item and video.
 *
 * @param videoValue The BCVideo to use
 * @param playerItemValue The AVPlayerItem to use
 */
- (id)initWithVideo:(BCVideo *)videoValue andItem:(AVPlayerItem *)playerItemValue;

/**
 * Factory initializer, constructs a new BCPlayerItem with the given player
 * item and video.
 *
 * @param videoValue The BCVideo to use
 * @param playerItemValue The AVPlayerItem to use
 */
+ (id)itemWithVideo:(BCVideo *)videoValue andItem:(AVPlayerItem *)playerItemValue;

///---------------------------------------------------------------------------------------
/// @name Item Data
///---------------------------------------------------------------------------------------

/**
 * The AVPlayerItem instance managed by this BCPlayerItem.
 */
@property (nonatomic, retain) AVPlayerItem *playerItem;

/**
 * The BCVideo instance managed by this BCPlayerItem.
 */
@property (nonatomic, readonly) BCVideo *video;

@end
