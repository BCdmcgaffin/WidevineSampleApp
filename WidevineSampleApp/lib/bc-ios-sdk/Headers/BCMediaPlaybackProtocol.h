//
//  BCMediaPlaybackProtocol.h
//  BCiOSLibrary
//
//  Created by Jim R. Wilson on 6/14/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVTime.h>

/**
 * The BCMediaPlayback protocol specifies methods for initiating and monitoring 
 * the progress of media (video) playback.  Its features are inspired by Apple’s
 * MPMediaPlayback protocol and the AVPlayer class: the interfaces should be 
 * familiar to developers who have worked with the Media Player and AV 
 * Foundation frameworks before while offering additional features and a 
 * higher-level of abstraction.
 * 
 * The BCMediaPlayback protocol supports basic playback operations including 
 * play, pause, and seeking to a particular point in the timeline.  It also 
 * provides observation points for receiving updates about the status of 
 * playback.
 */
@protocol BCMediaPlaybackProtocol <NSObject>

///-----------------------------------------------------------------------------
/// @name Starting and Stopping Playback
///-----------------------------------------------------------------------------

/**
 * Halts playback of the current BCVideo.
 *
 * Has no effect if playback was not underway when called.
 */
- (void)pause;

/**
 * Initiates playback of the current BCVideo.
 *
 * If playback was previously paused, play will resume from the position where 
 * playback left off.
 */
- (void)play;

///-----------------------------------------------------------------------------
/// @name Seeking within Videos
///-----------------------------------------------------------------------------

/**
 * Causes the player to seek forward or backward to the specified position.
 *@param time an NSTimeInterval object which specifies the time to seek.
 */
- (void)seekTo:(NSTimeInterval)time;

@end
