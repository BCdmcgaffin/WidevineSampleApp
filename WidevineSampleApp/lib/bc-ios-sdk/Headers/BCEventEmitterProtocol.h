//
//  BCEventEmitterProtocol.h
//  iOS-SDK-Sample-APP
//
//  Created by Keith Peters on 5/2/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

@class BCEvent;

/**
 * type of callback blocks.
 */
typedef void (^BCCallbackBlock)(BCEvent *event);

/**
 * type of generic blocks (blocks that take no arguments and return void).
 */
typedef void (^BCBlock)();

/**
 * Defines the interface for an event emitter that can receive and emit events.
 */
@protocol BCEventEmitterProtocol<NSObject>

///-----------------------------------------------------------------------------
/// @name Adding and Removing Listeners
///-----------------------------------------------------------------------------

/**
 * Allows an object to add itself as a listener for a type of event by passing
 * in a block to be invoked when an event of that type is emitted.
 * 
 * @param type The type of Event to listen for.
 * @param block The block to invoke, should conform to the following signature:
 * > void (^)(BCEvent *)
 * @return Returns an opaque object which can be used to remove the listener
 * later through the off:type:removeListener method.
 */
- (id)on:(NSString *)type callBlock:(BCCallbackBlock)block;

/**
 * Allows an object to add itself as a listener for a type of event by passing
 * in a block to be invoked when an event of that type is emitted.  Immediately
 * before invoking the block, the listener will be automatically removed,
 * however an opaque object is still returned so the listener may be removed
 * before it executes.
 *
 * @param type The type of Event to listen for.
 * @param block The block to invoke, should conform to the following signature:
 * > void (^)(BCEvent *)
 * @return Returns an opaque object which can be used to remove the listener
 * later through the off:type:removeListener method.
 */
- (id)once:(NSString *)type callBlock:(BCCallbackBlock)block;

/**
 * Removes a listener from the list of listeners for the given type. If no
 * previously added listener matches the parameters, calling this method has
 * no effect.
 *
 * @param type The type of Event to listen for.
 * @param listener The opaque object returned previously by the
 * on:callBlock: method.
 */
- (void)off:(NSString *)type removeListener:(id)listener;

///-----------------------------------------------------------------------------
/// @name Emitting Events
///-----------------------------------------------------------------------------

/**
 * Sends an event of the given type to all listeners for that type, passing
 * through details object, which can be nil.  After all listeners have been
 * invoked, the callback block is executed with the generated event.
 *
 * @warning Be careful when using thenCallBlock in apps with manual memory 
 * management. Such blocks cannot be cancelled so all objects referenced within 
 * them must not be deallocated until all listeners have been notified and the 
 * block has run.
 *
 * @param type The type of Event to emit.
 * @param details Dictionary of additional details relevant to this event
 * (may be nil).
 * @param callbackBlock The callback to execute after all listeners have been
 * called.
 * @return The BCEvent object which was created for this emit.
 */
- (void)emit:(NSString *)type withDetails:(NSDictionary *)details thenCallBlock:(BCCallbackBlock)callbackBlock;

/**
 * Sends an event of the given type to all listeners for that type. After all
 * listeners have been invoked, the callback block is executed with the
 * generated event.
 *
 * @param type The type of Event to emit.
 * @param callbackBlock The callback to execute after all listeners have been
 * called.
 * @return The BCEvent object which was created for this emit.
 */
- (void)emit:(NSString *)type thenCallBlock:(BCCallbackBlock)callbackBlock;

/**
 * Sends an event of the given type to all listeners for that type, passing
 * through details object, which can be nil.
 *
 * @param type The type of Event to emit.
 * @param details Dictionary of additional details relevant to this event
 * (may be nil).
 * @return The BCEvent object which was created for this emit.
 */
- (void)emit:(NSString *)type withDetails:(NSDictionary *)details;

/**
 * Sends an event of the given type to all listeners for that type.
 *
 * @param type The type of Event to emit.
 * @return The BCEvent object which was created for this emit.
 */
- (void)emit:(NSString *)type;

///-----------------------------------------------------------------------------
/// @name Request-Reply Flow
///-----------------------------------------------------------------------------

/**
 * Emits an event of the specified type with the associated details.  The
 * emitter will listen for responses to this event and call the provided
 * responseBlock when the first response is encountered.  Additional responses
 * will be ignored.
 *
 * @param type The type of Event to emit.
 * @param details Dictionary of additional details relevant to this event. Must
 * not be nil since this is used to determine the matching response Event.
 * @param responseBlock The block of code to invoke when a response Event is
 * received.
 */
- (void)request:(NSString *)type withDetails:(NSDictionary *)details responseBlock:(BCCallbackBlock)responseBlock;

/**
 * Emits an event of the specified type as a response to a previous event.
 *
 * @param event The Event which is being responded to.
 * @param type The type of Event to emit.
 * @param details Dictionary of additional details relevant to this event.
 */
- (void)respond:(BCEvent *)event emit:(NSString *)type withDetails:(NSDictionary *)details;

@end

