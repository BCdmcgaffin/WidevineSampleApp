//
//  BCRenditionSelectionProtocol.h
//  BCiOSSDK
//
//  Created by David LaPalomento on 8/8/12.
//
//

#import <Foundation/Foundation.h>
@class AVPlayerItem;
@class BCVideo;
@class BCPlayerItem;
@class BCRendition;

/**
 * The protocol that must be supported by objects which can choose a rendition 
 * for a video. Components that implement this protocol should provide both 
 * method-based and event-based mechanisms for selecting renditions. If you're 
 * planning on utilizing a rendition selector, it is recommended you prefer 
 * event-based selection to maximize your player's modularity.
 */
@protocol BCRenditionSelectionProtocol <NSObject>

/**
 * Selects a suitable rendition from the specified BCVideo.
 * @param video The video to select from.
 * @return the selected rendition
 */
- (BCRendition *)selectRendition:(BCVideo *)video;

/**
 * Factory method to create a BCPlayerItem from a BCVideo object.
 *
 * @param video BCVideo Video to be converted to a BCPlayerItem
 * @return BCPlayerItem representation of the video.
 */
- (BCPlayerItem *)itemForVideo:(BCVideo *)videoValue;

/**
 * Returns the BCPlayerItem associated with an AVPlayerItem. If none currently 
 * exists, a new BCPlayerItem is constructed and returned.
 * @param displayItem the AVPlayerItem to query.
 * @return the associated player item.
 */
- (BCPlayerItem *)getAssociatedItem:(AVPlayerItem *)displayItem;

@end
