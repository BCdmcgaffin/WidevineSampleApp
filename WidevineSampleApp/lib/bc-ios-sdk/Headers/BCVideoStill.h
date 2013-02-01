//
//  BCVideoStill.h
//  BCiOSSDK
//
//  Created by Jim R. Wilson on 8/9/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BCComponent.h"

/**
 * A visual component that shows a video still.
 *
 * ### Allowed to Emit
 *
 * This component may emit the following events:
 *
 *  - BCEventError - when an error occurs
 *  - BCEventDidSetVideoStill - to report that the video still has been set
 *
 * ### Allowed Listeners
 *
 * This component may listen for the following events:
 *
 *  - BCEventSetVideoStill - to respond by setting the video still
 *  - BCEventVideoWillPlay - to respond by hiding the video still
 */
@interface BCVideoStill : BCComponent

///-----------------------------------------------------------------------------
/// @name Creating the Component
///-----------------------------------------------------------------------------

/**
 * Designated initializer. Initializes the component with the given emitter and
 * parent view.  Upon initialization, this component will insert its own
 * UIImageView into the provided parent view.
 *
 * @param eventEmitter The upstream event emitter to communicate through.
 * @param viewValue The UIView into which this component will render itself.
 * @return the initialized object.
 */
- (id)initWithEventEmitter:(BCEventEmitter *)eventEmitter andView:(UIView *)viewValue;

@end
