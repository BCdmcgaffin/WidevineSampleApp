//
//  BCEvent.h
//  iOS-SDK-Sample-APP
//
//  Created by Keith Peters on 5/1/12.
//  Copyright (c) 2012 Brightcove. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * Represents an event created by a     BCEventEmitter.
 */
@interface BCEvent : NSObject 
{
    NSString *type;
    NSDictionary *details;
    BOOL propagationStopped;
    BOOL defaultPrevented;
}

///---------------------------------------------------------------------------------------
/// @name Creating an Event
///---------------------------------------------------------------------------------------

/**
 * Designated initializer, requires the type of event and any details.
 * @param eventType The type of the event.
 * @param eventDetails Dictionary of supporting details for this event, may be nil.
 * @return Returns the initialized event object.
 */
- (id)initWithType:(NSString *)eventType details:(NSDictionary *)eventDetails;

/**
 * Factory initializer, requires the type of event and any details.
 * @param eventType The type of the event.
 * @param eventDetails Dictionary of supporting details for this event, may be nil.
 * @return Returns the initialized event object.
 */
+ (id)eventWithType:(NSString *)eventType details:(NSDictionary *)eventDetails;

///-----------------------------------------------------------------------------
/// @name Event Data
///-----------------------------------------------------------------------------

/**
 * Represents the type of this event.
 */
@property (nonatomic, retain) NSString *type;

/**
 * Contains and data that was passed with the event. May be nil for many events.
 */
@property (nonatomic, retain) NSDictionary *details;

/**
 * Whether or not the recipient of an event called stopPropagation on this
 * event.
 */
@property (readonly) BOOL propagationStopped;

/**
 * Whether or not the recipient of an event called preventDefault on this event.
 */
@property (readonly) BOOL defaultPrevented;

///-----------------------------------------------------------------------------
/// @name Other Methods
///-----------------------------------------------------------------------------

/**
 * When called, will cause the event to stop begin emitted to any other
 * objects that are listening for this event.
 */
- (void)stopPropagation;

/**
 * When called, will cause the event's defaultPrevented property to become
 * true permenantly.  Any listener may call preventDefault to signal to the
 * original caller of emit that whatever action it would have normally taken
 * should not happen.
 */
- (void)preventDefault;

@end

///-----------------------------------------------------------------------------
/// @name Event Types
///-----------------------------------------------------------------------------

/**
 * Request additional params to be added to the analytics base params.
 * @param baseParams A dictionary of key/value pairs to add to the analytics
 * base params.
 */
extern NSString* const BCEventAddAnalyticsBaseParams;
/**
 * Request a queueing display advance to the next item in the playback queue.
 */
extern NSString* const BCEventAdvanceQueue;
/**
 * Represents any event.
 */
extern NSString* const BCEventAny;
/**
 * A cue point event stands for a particular place in time and will be fired
 * whenever the position of the video head passes this time.  Passing the cue
 * point may occur in either direction and during playback or seeking.
 *
 * Although a cue point may be associated with a specific time, it will actually
 * be triggered at the nearest possible moment on or after that time. So a cue
 * point event will contain in its details both the start and end times inside
 * of which the cue points were triggered.
 *
 * @param cuePoints (required) NSArray of BCCuePoint objects which span the
 * start and end times.
 * @param startTime (required) NSNumber for the beginning of the time range
 * spanning the cue point.
 * @param endTime (required) NSNumber for the end of the time range spanning the
 * cue point.
 * @param method (required) NSString representing the kind of activity which
 * precipitated this event.  Either @"play" or @"seek".
 */
extern NSString* const BCEventCuePoint;
/**
 * Indicates a display component's UIView is now actively associated with a 
 * UIWindow. Normally, this means the video display is visible.
 */
extern NSString* const BCEventDidAddDisplayToWindow;
extern NSString* const BCEventDidAdvanceQueue;
/**
 * Indicates all `before` cue points for a video have fired.
 */
extern NSString* const BCEventDidEmitBeforeCuePoints;
extern NSString* const BCEventDidInsertQueueItem;
extern NSString* const BCEventDidRemoveAllQueueItems;
extern NSString* const BCEventDidRemoveQueueItem;
extern NSString* const BCEventDidSeekTo;
/**
 * Indicates that an AVPlayerItem had to be replaced with a copy.  This can
 * happen for example if a previously played item attempts to be reinserted and
 * is a consequence of the runtime's restriction that an AVPlayerItem may only
 * ever be associated with a single AVPlayer instance.
 * @param oldItem The AVPlayerItem being replaced.
 * @param newItem The replacement AVPlayerItem.
 */
extern NSString* const BCEventDidReplacePlayerItem;
/**
 * Indicates a rendition has been selected for playback for a video.
 * @param video The BCVideo that was queried to select the rendition
 * @param rendition The BCRendition that was selected
 */
extern NSString* const BCEventDidSelectRendition;
extern NSString* const BCEventDidSetActionAtItemEnd;
/**
 * Indicates that an AVPlayer is now configured to render its playback to the 
 * display. The Brightcove player manages multiple instances of AVPlayer in 
 * order to optimistically load queued content. When the playing video is 
 * changed, the player may dispose of the current active AVPlayer and replace it
 * with one that has been initialized in the background. Monitoring and 
 * responding to this event or interacting with the underlying AVPlayer instance
 * itself can cause subtle and hard to diagnose playback issues; it should only 
 * be attempted by advanced developers.
 */
extern NSString* const BCEventDidSetActiveAVPlayer;
/**
 * Acknowledge setting of the query parameters that will be included in
 * BCAnalytics requests.
 */
extern NSString* const BCEventDidSetAnalyticsBaseParams;
extern NSString* const BCEventDidSetCuePoint;
extern NSString* const BCEventDidSetCuePoints;
extern NSString* const BCEventDidSetPlaylist;      // Not referenced
extern NSString* const BCEventDidSetPlaylistIndex; // Not referenced
extern NSString* const BCEventDidSetRendition;
extern NSString* const BCEventDidSetVideo;
extern NSString* const BCEventDidSetVideoStill;
extern NSString* const BCEventEnableAirPlay;
extern NSString* const BCEventError;
/**
 * Indicates that ExternalPlayback (ex: AirPlay) is now active.
 */
extern NSString* const BCEventExternalPlaybackActive;
/**
 * Indicates that ExternalPlayback (ex: AirPlay) is no longer active.
 */
extern NSString* const BCEventExternalPlaybackInactive;
extern NSString* const BCEventFindPlaylist;
extern NSString* const BCEventFindVideo;
extern NSString* const BCEventFoundPlaylist;
extern NSString* const BCEventFoundVideo;
extern NSString* const BCEventHideControls;
extern NSString* const BCEventInsertQueueItem;
extern NSString* const BCEventPause;
extern NSString* const BCEventPaused;
extern NSString* const BCEventPlay;
/**
 * Fired when the active AVPlayer reports a rate change.
 */
extern NSString* const BCEventPlayerRateChange;
/**
 * Indicates the rate of playback has changed.
 * @param oldRate The previous playback rate
 * @param newRate The new playback rate
 */
extern NSString* const BCEventRateChange;
extern NSString* const BCEventReadyToPlay;
extern NSString* const BCEventRemoveAllQueueItems;
extern NSString* const BCEventRemoveQueueItem;
extern NSString* const BCEventSeekTo;
/**
 * Request a rendition be selected for playback from a given video.
 * @param video The BCVideo to query for renditions
 */
extern NSString* const BCEventSelectRendition;
/**
 * Set the action for the player to take when the currently playing video 
 * completes.
 * @param action An NSNumber corresponding to the AVPlayerItemActionAtItemEnd 
 * value to set
 */
extern NSString* const BCEventSetActionAtItemEnd;
/**
 * Indicates whether the display should enable external playback. This can be
 * used to indicate that AirPlay should be turned off, for instance.
 *
 * @param externalPlaybackActive if true, external playback is allowed
 * @see AVPlayer.allowsExternalPlayback
 */
extern NSString* const BCEventSetAllowsExternalPlayback;
/**
 * Set the query parameters that will be included in BCAnalytics requests.
 * @param baseParams A dictionary of params.
 */
extern NSString* const BCEventSetAnalyticsBaseParams;
extern NSString* const BCEventSetCuePoint;
extern NSString* const BCEventSetCuePoints;
/**
 * Indicates whether components should forward additional event details for debugging purposes.
 * @param debug if true, send additional details with each emitted event.
 */
extern NSString* const BCEventSetDebug;
extern NSString* const BCEventSetRendition;
extern NSString* const BCEventSetVideo;
extern NSString* const BCEventSetVideoStill;
extern NSString* const BCEventShowControls;
extern NSString* const BCEventSliderBegin;
extern NSString* const BCEventSliderEnd;
extern NSString* const BCEventVideoDidEnd;
extern NSString* const BCEventVideoDidPlay;
extern NSString* const BCEventVideoDurationChanged;
extern NSString* const BCEventVideoProgress;
extern NSString* const BCEventVideoWillPlay;
/**
 * To indicate the current player item is about to be changed.
 * @param oldItem The AVPlayerItem that is currently loaded into the player
 * @param newItem The AVPlayerItem that is to replace the old item or nil
 */
extern NSString* const BCEventWillChangeItem;
