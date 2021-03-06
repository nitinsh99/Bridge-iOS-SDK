//
//  BridgeSDK.h
//  BridgeSDK
//
//  Created by Erin Mounts on 9/8/14.
//
//	Copyright (c) 2014-2015, Sage Bionetworks
//	All rights reserved.
//
//	Redistribution and use in source and binary forms, with or without
//	modification, are permitted provided that the following conditions are met:
//	    * Redistributions of source code must retain the above copyright
//	      notice, this list of conditions and the following disclaimer.
//	    * Redistributions in binary form must reproduce the above copyright
//	      notice, this list of conditions and the following disclaimer in the
//	      documentation and/or other materials provided with the distribution.
//	    * Neither the name of Sage Bionetworks nor the names of BridgeSDk's
//		  contributors may be used to endorse or promote products derived from
//		  this software without specific prior written permission.
//
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
//	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//	DISCLAIMED. IN NO EVENT SHALL SAGE BIONETWORKS BE LIABLE FOR ANY
//	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
//	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
//	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
//	ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//

#import <UIKit/UIKit.h>

#ifdef __cplusplus
extern "C" {
#endif
  
//! Project version number for BridgeSDK.
extern double BridgeSDKVersionNumber;

//! Project version string for BridgeSDK.
extern const unsigned char BridgeSDKVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <BridgeSDK/PublicHeader.h>
  
#import <BridgeSDK/SBBActivityManager.h>
#import <BridgeSDK/SBBAuthManager.h>
#import <BridgeSDK/SBBBridgeNetworkManager.h>
#import <BridgeSDK/SBBBridgeAppDelegate.h>
#import <BridgeSDK/SBBComponent.h>
#import <BridgeSDK/SBBComponentManager.h>
#import <BridgeSDK/SBBConsentManager.h>
#import <BridgeSDK/SBBUserManager.h>
#import <BridgeSDK/SBBObjectManager.h>
#import <BridgeSDK/SBBNetworkManager.h>
#import <BridgeSDK/SBBScheduleManager.h>
#import <BridgeSDK/SBBSurveyManager.h>
#import <BridgeSDK/SBBUploadManager.h>
#import <BridgeSDK/SBBErrors.h>
#import <BridgeSDK/SBBBridgeObjects.h>
#import <BridgeSDK/NSDate+SBBAdditions.h>
#import <BridgeSDK/NSBundle+SBBAdditions.h>
#import <BridgeSDK/UIDevice+Hardware.h>

  
// This sets the default environment at app (not SDK) compile time to Staging for debug builds and Production for non-debug.
#if DEBUG
#define kDefaultEnvironment SBBEnvironmentStaging
#else
#define kDefaultEnvironment SBBEnvironmentProd
#endif
static SBBEnvironment gDefaultEnvironment = kDefaultEnvironment;

// The default number of days to cache
extern const NSInteger SBBDefaultCacheDaysAhead;
extern const NSInteger SBBDefaultCacheDaysBehind;

// The maximum number of days that are supported for caching.
extern const NSInteger SBBMaxSupportedCacheDays;
  
@interface BridgeSDK : NSObject

/*!
 * Set up the Bridge SDK for the given study and pointing at the production environment.
 * Usually you would call this at the beginning of your AppDelegate's application:didFinishLaunchingWithOptions: method.
 *
 * This will register a default SBBNetworkManager instance conigured correctly for the specified study and appropriate
 * server environment. If you register a custom (or custom-configured) NetworkManager yourself, don't call this method.
 *
 * Caching is turned off if `cacheDaysAhead = 0` AND `cacheDaysBehind = 0`
 *
 *  @param study   A string identifier for your app's Bridge study, assigned to you by Sage Bionetworks.
 *  @param cacheDaysAhead Number of days ahead to cache.
 *  @param cacheDaysBehind Number of days behind to cache.
 */
+ (void)setupWithStudy:(NSString *)study cacheDaysAhead:(NSInteger)cacheDaysAhead cacheDaysBehind:(NSInteger)cacheDaysBehind;

/*!
 * Convenience method for setting up the study with default caching for days ahead and days behind.
 *
 * If `useCache` is set to `YES` then this method sets up caching using `SBBDefaultCacheDaysAhead` and 
 * `SBBDefaultCacheDaysBehind`
 *
 *  @param study   A string identifier for your app's Bridge study, assigned to you by Sage Bionetworks.
 *  @param useCache A flag indicating whether to use the SDK's built-in persistent caching. Pass NO if you want to handle this yourself.
 */
+ (void)setupWithStudy:(NSString *)study useCache:(BOOL)useCache;

/*!
 * Convenience method for setting up the study with caching turned off (default).
 */
+ (void)setupWithStudy:(NSString *)study;

/*!
 * Set up the Bridge SDK for the given study and server environment. Usually you would only call this version
 * of the method from test suites, or if you have a non-DEBUG build configuration that you don't want running against
 * the production server environment. Otherwise call the version of the setupWithStudy: method that doesn't
 * take an environment parameter, and let the SDK use the default environment.
 *
 * This will register a default SBBNetworkManager instance conigured correctly for the specified environment and study.
 * If you register a custom (or custom-configured) NetworkManager yourself, don't call this method.
 *
 * Caching is turned off if `cacheDaysAhead = 0` AND `cacheDaysBehind = 0`
 *
 *  @param study   A string identifier for your app's Bridge study, assigned to you by Sage Bionetworks.
 *  @param cacheDaysAhead Number of days ahead to cache.
 *  @param cacheDaysBehind Number of days behind to cache.
 *  @param environment Which server environment to run against.
 */
+ (void)setupWithStudy:(NSString *)study cacheDaysAhead:(NSInteger)cacheDaysAhead cacheDaysBehind:(NSInteger)cacheDaysBehind environment:(SBBEnvironment)environment;

/*!
 * For backward compatibility only. Use setupWithStudy:cacheDaysAhead:cacheDaysBehind:environment: instead (which this method calls).
 */
+ (void)setupWithStudy:(NSString *)study environment:(SBBEnvironment)environment __deprecated;

/*!
 * For backward compatibility only. Use setupWithStudy:cacheDaysAhead:cacheDaysBehind:environment: instead (which this method calls).
 */
+ (void)setupWithStudy:(NSString *)study useCache:(BOOL)useCache environment:(SBBEnvironment)environment __deprecated;

/*!
 * For backward compatibility only. Use setupWithStudy: instead (which this method calls).
 */
+ (void)setupWithAppPrefix:(NSString *)appPrefix __deprecated;

/*!
 * For backward compatibility only. Use setupWithStudy:cacheDaysAhead:cacheDaysBehind:environment: instead (which this method calls).
 */
+ (void)setupWithAppPrefix:(NSString *)appPrefix environment:(SBBEnvironment)environment __deprecated;

@end

#ifdef __cplusplus
}
#endif

