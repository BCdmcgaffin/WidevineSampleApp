//
//  BCQueueDisplay.h
//  BCiOSSDK
//
//  Created by David LaPalomento on 7/31/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import "BCComponent.h"

@class AVPlayer;
@class BCPlayerView;
@class UIView;

enum AVPlayerActionAtItemEnd;

/**
 * A visual component that plays back a sequence of videos by managing an
 * AVQueuePlayer instance.
 */
@interface BCQueueDisplay : BCComponent 

///-----------------------------------------------------------------------------
/// @name Creating the Component
///-----------------------------------------------------------------------------

/**
 * Designated initializer. Initializes the component with the given emitter and 
 * view.
 *
 * @param eventEmitter The upstream event emitter to communicate through.
 * @param frame The frame rectangle for the view, rendered in points.
 * @return the initialized object.
 */
- (id)initWithEventEmitter:(BCEventEmitter *)eventEmitter andFrame:(CGRect)frame;

///-----------------------------------------------------------------------------
/// @name Video Display Data
///-----------------------------------------------------------------------------

/**
 * Action to take when the end of one queued video is reached. Behaves
 * identically to AVQueuePlayer's actionAtItemEnd property. The component will
 * take this value from the 'action' property of a BCEventSetActionAtItemEnd's
 * details.
 *
 * Valid values are:
 * - AVPlayerActionAtItemEndAdvance  = 0, (default)
 * - AVPlayerActionAtItemEndPause    = 1,
 * - AVPlayerActionAtItemEndNone     = 2,
 */
@property (nonatomic, readonly) AVPlayerActionAtItemEnd actionAtItemEnd;

/**
 * The BCPlayerView that will display the video.
 */
@property (nonatomic, readonly) BCPlayerView *view;

/**
 * The AVPlayer instance that controls the video playing.
 */
- (AVPlayer *)activePlayer;

/**
 * The backup instance of AVPlayer which is not currently active.
 */
- (AVPlayer *)inactivePlayer;

/**
 * An array of the AVPlayerItems in the queue.
 */
@property (nonatomic, readonly) NSArray *items;

@end
