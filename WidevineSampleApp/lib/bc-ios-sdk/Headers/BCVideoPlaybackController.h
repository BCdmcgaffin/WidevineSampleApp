//
//  BCVideoPlaybackController.h
//  BCiOSLibrary
//
//  Created by Keith Peters on 5/17/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import "BCComponent.h"
#import "BCCuePoint.h"

/**
 * Controls the playback of a video including starting, stopping, firing cue
 * points.
 */
@interface BCVideoPlaybackController : BCComponent

/**
 * An array of cue points.
 */
@property (nonatomic, retain) NSMutableArray *cuePoints;

/**
 * Checks for cue points during the playback of a video.
 */
- (void)checkMidCuePointWithMethod:(NSString *)method;

/**
 * Checks for an after cue point when video ends.
 */
- (void)checkEndCuePoint;

/**
 * Emits a cue point event with correct details.
 */
- (void)emitCuePointEvent:(NSMutableArray *)activeCuePoints method:(NSString *)method withBlock:(BCBlock)callbackBlock;


@end
