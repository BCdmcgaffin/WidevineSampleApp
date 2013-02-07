# Widevine Sample App for Brightcove #

This app allows you to playback a selection of videos that have been
protected with [Widevine](http://www.widevine.com), Google's DRM
solution. Playback is available with the combination of the [Brightcove
Video Cloud Player SDK for
iOS](http://support.brightcove.com/en/video-cloud/docs/brightcove-video-cloud-player-sdk-ios)
and its [Widevine
Plugin](http://support.brightcove.com/en/video-cloud/docs/widevine-plugin-brightcove-video-cloud-player-sdk-ios).
You should feel free to use any of the code in this sample for your own
iOS apps for Widevine playback.

## Installation ##

This app will soon be available in the App Store, but if you have XCode
installed, you can build and run it yourself.

### requirements ###

* XCode
* git

### running the app ###

1. Clone this repository. In the **Terminal** app type:

    ```
    $ git clone git@github.com:BCdmcgaffin/WidevineSampleApp.git 
    ```

1. Open the project in XCode. You can do this from Terminal like so:
    ```
    $ open WidevineSampleApp/WidevineSampleApp.xcodeproj
    ```

1. The app will not run in an iOS Simulator, so select your connected
   iPhone or iPad with at least iOS 5.0 installed and **Run** the app.

## Usage ##

### Integrating your app with the Brightcove Media API.
Adding a Widevine player to an iOS view is pretty simple:  You just:

1. initialize your application
2. initialize the Widevine plugin.
3. search for videos in your account to populate the player

### Restrictions using the Google Widevine SDK

The Widevine Plugin for the BC iOS SDK uses the Widevine SDK provided by Google. This introduces a few restrictions that you should know about:

* When developing with the Widevine SDK provided by Google, you will not be able to build or run your app with the iOS simulator. Widevine's library requires hardware features that are not available in the iOS Simulator.
* Because of security concerns, Widevine playback will not work over AirPlay. This should not affect app development but will prevent users from redirecting playback of a Widevine-packaged video to an AirPlay device.

### Initialize your application
You can store your Read API token in a plist file (see `widevine.plist`)
and retrieve it during runtime to initialize the BC iOS SDK and fetch
videos. Note the `#import` statements at the top of `ViewController.m`.
Be sure to include appropriate `#import` statements for the SDK classes
that you need. Here we list all of the header files that we will be
referencing in the `ViewController` implementation.

```objective-c
#import "BCQueuePlayer.h"
#import "BCVideo.h"
#import "BCCatalog.h"
#import "BCEventLogger.h"
#import "BCUIControls.h"
#import "BCPlaylist.h"
#import "BCEvent.h"
#import "BCWidevinePlugin.h"

#import "WidevineInfo.h"
#import "ViewController.h"
```

When the initial view loads, your app should initialize the Widevine
plugin. This will register your media api token and create a
`BCQueuePlayer` that you can add to your app.

```objective-c
// Initialize the Widevine plugin, passing a media api token stored in a
// property list file.
NSString     *path = [[NSBundle mainBundle] pathForResource:@"widevine" ofType:@"plist"];
NSDictionary *dictionary = [NSDictionary dictionaryWithContentsOfFile:path];
NSString     *token = [dictionary objectForKey:@"mediaApiToken"];

BCWidevinePlugin *widevinePlugin = [[BCWidevinePlugin alloc] initWithToken:token];
BCQueuePlayer *player = widevinePlugin.player;
```

Once the plugin is initialized, your app is ready to find videos from
your catalog and prepare them for playback.
```objective-c

// Search for a playlist by a reference id.
[widevinePlugin findPlaylistByReferenceID:[dictionary objectForKey:@"iosPlaylistReferenceId"]
                                  options:nil
                                callBlock:^(BCError *error, BCPlaylist *playlist) {
                                    
                                    if (playlist) {
                                        [self createInfoViewWithPlaylist:playlist];

                                        BCVideo *firstVideo = [playlist.videos objectAtIndex:0];
                                        if (firstVideo) {
                                          [widevinePlugin queueVideo:firstVideo];
                                        }
                                    } else if (error) {
                                        [self displayErrorAlert:error.description];
                                    }
                                }];
```
`BCWidevinePlugin` provides four methods for searching your catalog for
videos:

* `findVideoByID`
* `findVideoByReferenceID`
* `findPlaylistByID`
* `findPlaylistByReferenceID`

You can add some UI controls for your player, like so:
```objective-c
UIView *controlsView = [[UIView alloc] initWithFrame:CGRectMake(0, 180, 320, 50)];
[self.view addSubview:controlsView];
controlsComponent = [[BCUIControls alloc] initWithEventEmitter:player.playbackEmitter andView:controlsView];
```

Once you have retrieved videos with one of the API methods above, and
added controls to your player that are initalized with the
`playbackEmitter`, playback will begin when the user presses the Play
button on the player. You can also begin playback with:
```objective-c
[player play];
```
If you have queued multiple videos in the plugin and would like the next
video to play when the first video ends, you can turn on the `autoPlay`
property:
```objective-c
widevinePlugin.autoPlay = YES;
```

If you would like a debug log to help troubleshoot your app, you can
create a logger, passing it the `eventEmitter` property that is
initialized in the `createPlayer` method. If you turn on verbose logging,
the log will include the contents of the `BCEvent.details` property. It
can be helpful, but it does make it harder to browse through the list of
events emitted by the BC iOS SDK.

```objective-c
    BCQueuePlayer *player = self.widevinePlugin.player;
    BCEventLogger *logger = [[BCEventLogger alloc] initWithEventEmitter:player.playbackEmitter];
    [logger setVerbose:NO];
}
```

If you save the `eventEmitter` property, you can listen for BC iOS SDK
events and take appropriate action when they are emitted. The
Widevine Plugin adds an additional event, `BCWidevineEvent`, which simply
relays events from the Widevine library to let you know when certain
playback events are emitted, such as playback start and stop, bitrate
change, playback failure, and more. In this example, we are simply
printing the Widevine event to log output:

```objective-c
    BCEventEmitter *eventEmitter = player.playbackEmitter;

    UIView *controlsView = [[UIView alloc] initWithFrame:CGRectMake(0, 180, 320, 50)];
    [self.view addSubview:controlsView];
    controlsComponent = [[BCUIControls alloc] initWithEventEmitter:eventEmitter andView:controlsView];
}
```

If you want to catch Widevine-specific events, you could configure an event listener like this:

```objective-c
[eventEmitter on:BCEventWidevine callBlock:^(BCEvent *event) {
  NSLog(@"Widevine event details: %@", event.details);
}];
```

`ViewController.m` contains the bulk of the code necessary to implement a Widevine Player in iOS. If
you have any questions, you can post them in the *iPhone SDK* forum at
[http://community.brightcove.com](http://community.brightcove.com).

If you would like more information about the BC iOS SDK, you can check
the documentation at http://docs.brightcove.com/en/bc-ios-sdk/.
