//
//  BCRegisteringEventEmitter.h
//  iOS-SDK-Sample-APP
//
//  Created by Keith Peters on 5/2/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import "BCEventEmitterProtocol.h"

@class BCEventEmitter;
@class BCComponent;

/**
 * An event emitter used within components. Manages event listeners and ensures 
 * they are properly unregistered when the component is deallocated. Validates 
 * any listeners and event emissions attempted by the component against list of 
 * events it is allowed to listen for or emit.
 * 
 * See the BCEventEmitterProtocol for more information on what an event emitter
 * does.
 */
@interface BCRegisteringEventEmitter : NSObject <BCEventEmitterProtocol>
{
    BCEventEmitter *emitter;
    NSArray *allowedEmits;
    NSArray *allowedListeners;
}

///---------------------------------------------------------------------------------------
/// @name Creating a Registering Event Emitter
///---------------------------------------------------------------------------------------

/**
 * Designated initializer. Initializes the instance with a main event emitter
 * and a component class. When listening for or emitting events, the type of the event
 * is validated against the list of events allowed by the component class.  If the
 * event is not valid, an exception is thrown.
 * 
 * @param eventEmitter The upstream event emitter through which to emit events and add listeners.
 * @param componentClass The component class which this emitter will validate actions against.
 */
- (id)initWithEmitter:(id<BCEventEmitterProtocol>)eventEmitter componentClass:(Class)componentClass;

@end
