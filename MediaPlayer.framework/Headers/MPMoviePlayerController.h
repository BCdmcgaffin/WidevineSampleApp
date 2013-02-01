//
//  MPMoviePlayerController.h
//  MediaPlayer
//
//  Copyright 2008-2010 Apple, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <MediaPlayer/MPMediaPlayback.h>
#import <UIKit/UIKit.h>

@class MPMovieAccessLog, MPMovieErrorLog;

// -----------------------------------------------------------------------------
// Types

enum {
    MPMovieScalingModeNone,       // No scaling
    MPMovieScalingModeAspectFit,  // Uniform scale until one dimension fits
    MPMovieScalingModeAspectFill, // Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
    MPMovieScalingModeFill        // Non-uniform scale. Both render dimensions will exactly match the visible bounds
};
typedef NSInteger MPMovieScalingMode;

enum {
    MPMoviePlaybackStateStopped,
    MPMoviePlaybackStatePlaying,
    MPMoviePlaybackStatePaused,
    MPMoviePlaybackStateInterrupted,
    MPMoviePlaybackStateSeekingForward,
    MPMoviePlaybackStateSeekingBackward
};
typedef NSInteger MPMoviePlaybackState;

enum {
    MPMovieLoadStateUnknown        = 0,
    MPMovieLoadStatePlayable       = 1 << 0,
    MPMovieLoadStatePlaythroughOK  = 1 << 1, // Playback will be automatically started in this state when shouldAutoplay is YES
    MPMovieLoadStateStalled        = 1 << 2, // Playback will be automatically paused in this state, if started
};
typedef NSInteger MPMovieLoadState;

enum {
    MPMovieRepeatModeNone,
    MPMovieRepeatModeOne
};
typedef NSInteger MPMovieRepeatMode;

enum {
    MPMovieControlStyleNone,       // No controls
    MPMovieControlStyleEmbedded,   // Controls for an embedded view
    MPMovieControlStyleFullscreen, // Controls for fullscreen playback
    
    MPMovieControlStyleDefault = MPMovieControlStyleEmbedded
};
typedef NSInteger MPMovieControlStyle;

enum {
    MPMovieFinishReasonPlaybackEnded,
    MPMovieFinishReasonPlaybackError,
    MPMovieFinishReasonUserExited
};
typedef NSInteger MPMovieFinishReason;

// -----------------------------------------------------------------------------
// Movie Property Types

enum {
    MPMovieMediaTypeMaskNone  = 0,
    MPMovieMediaTypeMaskVideo = 1 << 0,
    MPMovieMediaTypeMaskAudio = 1 << 1
};
typedef NSInteger MPMovieMediaTypeMask;

enum {
    MPMovieSourceTypeUnknown,
    MPMovieSourceTypeFile,     // Local or progressively downloaded network content
    MPMovieSourceTypeStreaming // Live or on-demand streaming content
};
typedef NSInteger MPMovieSourceType;

// -----------------------------------------------------------------------------
// Movie Player
// 
// See MPMediaPlayback.h for the playback methods.

MP_EXTERN_CLASS_AVAILABLE(2_0) @interface MPMoviePlayerController : NSObject <MPMediaPlayback> {
@private
    void *_internal;
}

- (id)initWithContentURL:(NSURL *)url;

@property(nonatomic, copy) NSURL *contentURL;

// The view in which the media and playback controls are displayed.
@property(nonatomic, readonly) UIView *view;

// A view for customization which is always displayed behind movie content.
@property(nonatomic, readonly) UIView *backgroundView;

// Returns the current playback state of the movie player.
@property(nonatomic, readonly) MPMoviePlaybackState playbackState;

// Returns the network load state of the movie player.
@property(nonatomic, readonly) MPMovieLoadState loadState;

// The style of the playback controls. Defaults to MPMovieControlStyleDefault.
@property(nonatomic) MPMovieControlStyle controlStyle;

// Determines how the movie player repeats when reaching the end of playback. Defaults to MPMovieRepeatModeNone.
@property(nonatomic) MPMovieRepeatMode repeatMode;

// Indicates if a movie should automatically start playback when it is likely to finish uninterrupted based on e.g. network conditions. Defaults to YES.
@property(nonatomic) BOOL shouldAutoplay;

// Determines if the movie is presented in the entire screen (obscuring all other application content). Default is NO.
// Setting this property to YES before the movie player's view is visible will have no effect.
@property(nonatomic, getter=isFullscreen) BOOL fullscreen;
- (void)setFullscreen:(BOOL)fullscreen animated:(BOOL)animated;

// Determines how the content scales to fit the view. Defaults to MPMovieScalingModeAspectFit.
@property(nonatomic) MPMovieScalingMode scalingMode;

// Returns YES if the first video frame has been made ready for display for the current item.
// Will remain NO for items that do not have video tracks associated.
@property(nonatomic, readonly) BOOL readyForDisplay NS_AVAILABLE_IOS(6_0);

@end

// -----------------------------------------------------------------------------
// Movie properties of the current movie prepared for playback.

@interface MPMoviePlayerController (MPMovieProperties)

// The types of media in the movie, or MPMovieMediaTypeNone if not known.
@property(nonatomic, readonly) MPMovieMediaTypeMask movieMediaTypes;

// The playback type of the movie. Defaults to MPMovieSourceTypeUnknown.
// Specifying a playback type before playing the movie can result in faster load times.
@property(nonatomic) MPMovieSourceType movieSourceType;

// The duration of the movie, or 0.0 if not known.
@property(nonatomic, readonly) NSTimeInterval duration;

// The currently playable duration of the movie, for progressively downloaded network content.
@property(nonatomic, readonly) NSTimeInterval playableDuration;

// The natural size of the movie, or CGSizeZero if not known/applicable.
@property(nonatomic, readonly) CGSize naturalSize;

// The start time of movie playback. Defaults to NaN, indicating the natural start time of the movie.
@property(nonatomic) NSTimeInterval initialPlaybackTime;

// The end time of movie playback. Defaults to NaN, which indicates natural end time of the movie.
@property(nonatomic) NSTimeInterval endPlaybackTime;

// Indicates whether the movie player allows AirPlay video playback. Defaults to YES on iOS 5.0 and later.
@property(nonatomic) BOOL allowsAirPlay NS_AVAILABLE_IOS(4_3);

// Indicates whether the movie player is currently playing video via AirPlay.
@property(nonatomic, readonly, getter=isAirPlayVideoActive) BOOL airPlayVideoActive NS_AVAILABLE_IOS(5_0);

@end

// -----------------------------------------------------------------------------
// Movie Player Notifications

// Posted when the scaling mode changes.
MP_EXTERN NSString *const MPMoviePlayerScalingModeDidChangeNotification;

// Posted when movie playback ends or a user exits playback.
MP_EXTERN NSString *const MPMoviePlayerPlaybackDidFinishNotification;

MP_EXTERN NSString *const MPMoviePlayerPlaybackDidFinishReasonUserInfoKey NS_AVAILABLE_IOS(3_2); // NSNumber (MPMovieFinishReason)

// Posted when the playback state changes, either programatically or by the user.
MP_EXTERN NSString *const MPMoviePlayerPlaybackStateDidChangeNotification NS_AVAILABLE_IOS(3_2);

// Posted when the network load state changes.
MP_EXTERN NSString *const MPMoviePlayerLoadStateDidChangeNotification NS_AVAILABLE_IOS(3_2);

// Posted when the currently playing movie changes.
MP_EXTERN NSString *const MPMoviePlayerNowPlayingMovieDidChangeNotification NS_AVAILABLE_IOS(3_2);

// Posted when the movie player enters or exits fullscreen mode.
MP_EXTERN NSString *const MPMoviePlayerWillEnterFullscreenNotification NS_AVAILABLE_IOS(3_2);
MP_EXTERN NSString *const MPMoviePlayerDidEnterFullscreenNotification NS_AVAILABLE_IOS(3_2);
MP_EXTERN NSString *const MPMoviePlayerWillExitFullscreenNotification NS_AVAILABLE_IOS(3_2);
MP_EXTERN NSString *const MPMoviePlayerDidExitFullscreenNotification NS_AVAILABLE_IOS(3_2);
MP_EXTERN NSString *const MPMoviePlayerFullscreenAnimationDurationUserInfoKey NS_AVAILABLE_IOS(3_2); // NSNumber of double (NSTimeInterval)
MP_EXTERN NSString *const MPMoviePlayerFullscreenAnimationCurveUserInfoKey NS_AVAILABLE_IOS(3_2);     // NSNumber of NSUInteger (UIViewAnimationCurve)

// Posted when the movie player begins or ends playing video via AirPlay.
MP_EXTERN NSString *const MPMoviePlayerIsAirPlayVideoActiveDidChangeNotification NS_AVAILABLE_IOS(5_0);

// Posted when the ready for display state changes.
MP_EXTERN NSString *const MPMoviePlayerReadyForDisplayDidChangeNotification NS_AVAILABLE_IOS(6_0);

// -----------------------------------------------------------------------------
// Movie Property Notifications

// Calling -prepareToPlay on the movie player will begin determining movie properties asynchronously.
// These notifications are posted when the associated movie property becomes available.
MP_EXTERN NSString *const MPMovieMediaTypesAvailableNotification NS_AVAILABLE_IOS(3_2);
MP_EXTERN NSString *const MPMovieSourceTypeAvailableNotification NS_AVAILABLE_IOS(3_2); // Posted if the movieSourceType is MPMovieSourceTypeUnknown when preparing for playback.
MP_EXTERN NSString *const MPMovieDurationAvailableNotification NS_AVAILABLE_IOS(3_2);
MP_EXTERN NSString *const MPMovieNaturalSizeAvailableNotification NS_AVAILABLE_IOS(3_2);

// -----------------------------------------------------------------------------
// Thumbnails

enum {
    MPMovieTimeOptionNearestKeyFrame,
    MPMovieTimeOptionExact
};
typedef NSInteger MPMovieTimeOption;


@interface MPMoviePlayerController (MPMoviePlayerThumbnailGeneration)

// Returns a thumbnail at the given time.
- (UIImage *)thumbnailImageAtTime:(NSTimeInterval)playbackTime timeOption:(MPMovieTimeOption)option;

// Asynchronously request thumbnails for one or more times, provided as an array of NSNumbers (double).
// Posts MPMoviePlayerThumbnailImageRequestDidFinishNotification on completion.
- (void)requestThumbnailImagesAtTimes:(NSArray *)playbackTimes timeOption:(MPMovieTimeOption)option;

// Cancels all pending asynchronous thumbnail requests.
- (void)cancelAllThumbnailImageRequests;

@end

// Posted when each thumbnail image request is completed.
MP_EXTERN NSString *const MPMoviePlayerThumbnailImageRequestDidFinishNotification NS_AVAILABLE_IOS(3_2);
MP_EXTERN NSString *const MPMoviePlayerThumbnailImageKey NS_AVAILABLE_IOS(3_2); // UIImage, may be nil if an error occurred.
MP_EXTERN NSString *const MPMoviePlayerThumbnailTimeKey NS_AVAILABLE_IOS(3_2);  // NSNumber (double)
MP_EXTERN NSString *const MPMoviePlayerThumbnailErrorKey NS_AVAILABLE_IOS(3_2); // NSError

// -----------------------------------------------------------------------------
// Timed Metadata

@interface MPMoviePlayerController (MPMoviePlayerTimedMetadataAdditions)

// Returns an array of the most recent MPTimedMetadata objects provided by the media stream.
- (NSArray *)timedMetadata NS_AVAILABLE_IOS(4_0);

@end

MP_EXTERN_CLASS_AVAILABLE(4_0) @interface MPTimedMetadata : NSObject {
@private
    void *_internal;
}

// A key which identifies a piece of timed metadata.
@property(nonatomic, readonly) NSString *key;

// The namespace of the identifying key.
@property(nonatomic, readonly) NSString *keyspace;

// The object value of the metadata.
@property(nonatomic, readonly) id value;

// The timestamp of the metadata, in the timebase of the media stream.
@property(nonatomic, readonly) NSTimeInterval timestamp;

// A dictionary containing all metadata information associated with this object, which may hold additional key-specific data (see below).
@property(nonatomic, readonly) NSDictionary *allMetadata;

@end

// Posted when new timed metadata arrives.
MP_EXTERN NSString *const MPMoviePlayerTimedMetadataUpdatedNotification NS_AVAILABLE_IOS(4_0);
MP_EXTERN NSString *const MPMoviePlayerTimedMetadataUserInfoKey NS_AVAILABLE_IOS(4_0);       // NSArray of the most recent MPTimedMetadata objects.

// Additional dictionary keys for use with the 'allMetadata' property. All keys are optional.
MP_EXTERN NSString *const MPMoviePlayerTimedMetadataKeyName NS_AVAILABLE_IOS(4_0);           // NSString
MP_EXTERN NSString *const MPMoviePlayerTimedMetadataKeyInfo NS_AVAILABLE_IOS(4_0);           // NSString
MP_EXTERN NSString *const MPMoviePlayerTimedMetadataKeyMIMEType NS_AVAILABLE_IOS(4_0);       // NSString
MP_EXTERN NSString *const MPMoviePlayerTimedMetadataKeyDataType NS_AVAILABLE_IOS(4_0);       // NSString
MP_EXTERN NSString *const MPMoviePlayerTimedMetadataKeyLanguageCode NS_AVAILABLE_IOS(4_0);   // NSString (ISO 639-2)

// -----------------------------------------------------------------------------

@interface MPMoviePlayerController (MPMovieLogging)

// Returns an object that represents a snapshot of the network access log. Can be nil.
@property (nonatomic, readonly) MPMovieAccessLog *accessLog NS_AVAILABLE_IOS(4_3);

// Returns an object that represents a snapshot of the error log. Can be nil.
@property (nonatomic, readonly) MPMovieErrorLog *errorLog NS_AVAILABLE_IOS(4_3);

@end

// -----------------------------------------------------------------------------
// An MPMovieAccessLog accumulates key metrics about network playback and presents them as a collection of MPMovieAccessLogEvent instances.
// Each MPMovieAccessLogEvent instance collates the data that relates to each uninterrupted period of playback.

MP_EXTERN_CLASS_AVAILABLE(4_3) @interface MPMovieAccessLog : NSObject <NSCopying>

// Returns the webserver access log into a textual format that conforms to the W3C Extended Log File Format for web server log files.
// For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
@property (nonatomic, readonly) NSData *extendedLogData;

// Returns the string encoding of the extendedLogData property.
@property (nonatomic, readonly) NSStringEncoding extendedLogDataStringEncoding;

// An ordered collection of MPMovieAccessLogEvent instances that represent the chronological sequence of events contained in the access log.
@property (nonatomic, readonly) NSArray *events;

@end

// -----------------------------------------------------------------------------
// An MPMovieErrorLog provides data to identify if, and when, network resource playback failures occured.

MP_EXTERN_CLASS_AVAILABLE(4_3) @interface MPMovieErrorLog : NSObject <NSCopying>

// Returns the webserver error log into a textual format that conforms to the W3C Extended Log File Format for web server log files.
// For more information see: http://www.w3.org/pub/WWW/TR/WD-logfile.html
@property (nonatomic, readonly) NSData *extendedLogData;

// Returns the string encoding of the extendedLogData property.
@property (nonatomic, readonly) NSStringEncoding extendedLogDataStringEncoding;

// An ordered collection of MPMovieErrorLogEvent instances that represent the chronological sequence of events contained in the error log.
@property (nonatomic, readonly) NSArray *events;

@end

// -----------------------------------------------------------------------------
// An MPMovieAccessLogEvent repesents a single access log entry.

MP_EXTERN_CLASS_AVAILABLE(4_3) @interface MPMovieAccessLogEvent : NSObject <NSCopying>

// A count of media segments downloaded from the server to this client.
@property (nonatomic, readonly) NSUInteger numberOfSegmentsDownloaded;

// The date/time at which playback began for this event.
@property (nonatomic, readonly) NSDate *playbackStartDate;

// The URI of the playback item.
@property (nonatomic, readonly) NSString *URI;

// The IP address of the server that was the source of the last delivered media segment. Can be either an IPv4 or IPv6 address.
@property (nonatomic, readonly) NSString *serverAddress;

// A count of changes to the serverAddress property over the last uninterrupted period of playback.
@property (nonatomic, readonly) NSUInteger numberOfServerAddressChanges;

// A GUID that identifies the playback session. This value is used in HTTP requests.
@property (nonatomic, readonly) NSString *playbackSessionID;

// An offset into the playlist where the last uninterrupted period of playback began, in seconds. The value is negative if unknown.
@property (nonatomic, readonly) NSTimeInterval playbackStartOffset;

// The accumulated duration of the media downloaded, in seconds. The value is negative if unknown.
@property (nonatomic, readonly) NSTimeInterval segmentsDownloadedDuration;

// The accumulated duration of the media played, in seconds.
@property (nonatomic, readonly) NSTimeInterval durationWatched;

// The total number of playback stalls encountered. The value is negative if unknown.
@property (nonatomic, readonly) NSInteger numberOfStalls;

// The accumulated number of bytes transferred. The value is negative if unknown.
@property (nonatomic, readonly) int64_t numberOfBytesTransferred;

// The empirical throughput across all media downloaded, in bits per second.
@property (nonatomic, readonly) double observedBitrate;

// The throughput required to play the stream, as advertised by the server, in bits per second.
@property (nonatomic, readonly) double indicatedBitrate;

// The total number of dropped video frames.
@property (nonatomic, readonly) NSInteger numberOfDroppedVideoFrames;

@end

// -----------------------------------------------------------------------------
// An MPMovieErrorLogEvent repesents a single error log entry.

MP_EXTERN_CLASS_AVAILABLE(4_3) @interface MPMovieErrorLogEvent : NSObject <NSCopying>

// The date and time when the error occured.
@property (nonatomic, readonly) NSDate *date;

// The URI of the playback item.
@property (nonatomic, readonly) NSString *URI;

// The IP address of the server that was the source of the error.
@property (nonatomic, readonly) NSString *serverAddress;

// A GUID that identifies the playback session. This value is used in HTTP requests.
@property (nonatomic, readonly) NSString *playbackSessionID;

// A unique error code identifier. The value is negative if unknown.
@property (nonatomic, readonly) NSInteger errorStatusCode;

// The domain of the error.
@property (nonatomic, readonly) NSString *errorDomain;

// A description of the error encountered.
@property (nonatomic, readonly) NSString *errorComment;

@end

// -----------------------------------------------------------------------------
// Deprecated methods and properties
// These will be removed in a future release of iOS

typedef enum {
    MPMovieControlModeDefault,
    MPMovieControlModeVolumeOnly,
    MPMovieControlModeHidden
} MPMovieControlMode;

@interface MPMoviePlayerController (MPMoviePlayerDeprecated)

// Indicates if the movie player should inherit the application's audio session instead of creating a new session (which would interrupt the application's session).
// Defaults to YES. Setting this property during playback will not take effect until playback is stopped and started again.
@property(nonatomic) BOOL useApplicationAudioSession NS_DEPRECATED_IOS(3_2, 6_0);

// Use the backgroundView property instead.
- (void)setBackgroundColor:(UIColor *)backgroundColor NS_DEPRECATED_IOS(2_0, 3_2);
- (UIColor *)backgroundColor NS_DEPRECATED_IOS(2_0, 3_2);

// Use the movieControlStyle property instead.
- (void)setMovieControlMode:(MPMovieControlMode)movieControlMode NS_DEPRECATED_IOS(2_0, 3_2);
- (MPMovieControlMode)movieControlMode NS_DEPRECATED_IOS(2_0, 3_2);

@end

// This notification is superseded by MPMediaPlaybackIsPreparedToPlayDidChangeNotification.
MP_EXTERN NSString *const MPMoviePlayerContentPreloadDidFinishNotification NS_DEPRECATED_IOS(2_0, 3_2);
