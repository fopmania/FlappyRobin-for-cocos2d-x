#define kZindexTube 35
#ifndef Constants_h
#define Constants_h

#define kindexBG 0
#define kindexFloor 40
#define kindexTube 35
#define kindexRobin 100
#define kindexCloudFast 20
#define kindexCloudSlow 10
#define kindexTree 50
#define kindexMount 30

#define kRobinStateMoving 0
#define kRobinStateStopped 1
#define kRobinStartSpeedY 300

#define kDesignSizeH    640
#define kDesignSizeW    960

#define kImageSizeH     320
#define kImageSizeW     480

#define kImageMulti      kDesignSizeH/kImageSizeH

#define kCloudScaleSlow 0.4
#define kCloudScaleFast 0.85
#define kMountScale 0.8
#define kTreeScale 1.0

#define kCloudSpeedSlow 20.0
#define kCloudSpeedFast 55.0
#define kMountSpeed 40.0
#define kTreeSpeed  90.0

#define kRobinStateMoving 0
#define kRobinStateStopped 1
#define kRobinStartSpeedY 450

#define GRAVITY -1000

#define kTubeStateActive 0
#define kTubeStateInActive 1
#define kTubeInActiveX -1000

#define kTubeSpawnMinTime 1.8
#define kTubeSpawnTimeVariance 8

#define kTubeTypeUpper 0
#define kTubeTypeLower 1
#define kTubeTypePair 2
#define kTubeTypeNone 3

#define kGapRatio       1


#define kSingleGapTop 440 * kGapRatio
#define kSingleGapBottom 230 * kGapRatio
#define kSingleGapMax 280 * kGapRatio
#define kSingleGapMin 160  * kGapRatio

#define kDoubleGapTop 480 * kGapRatio
#define kDoubleGapBottom 120 * kGapRatio
#define kDoubleGapMax 220 * kGapRatio
#define kDoubleGapMin 140 * kGapRatio

#define kTubeMaxUpPixels 180

#define kFontName	"Marker Felt.ttf"

#define kSplash         "Kratos.png"
#define kFileBG			"BG-HD.png"
#define kFileFloor		"Floor-HD.png"
#define kFileRobin		"Robin-HD.png"
#define kFileCloud		"Cloud-HD.png"
#define kFileMount		"Mount-HD.png"
#define kFileTree		"Tree-HD.png"
#define kFileTube		"Tube-HD.png"

#define kFileBGM        "Marimba-music.mp3"

#define kEffectClick     "Button.wav"
#define kEffectSuccess   "Success1.wav"
#define kEffectExplosion "Explosion2.wav"
#define kEffectJump      "Jumping.wav"

#define     US_VOL_MUSIC    "US_VOL_MUSIC"
#define     US_VOL_EFFECT   "US_VOL_EFFECT"
#define     US_HIGH_SCORE   "US_HIGH_SCORE"

//#define kEffectClick    0
//#define kEffectRobinTap 1
//#define kEffectSuccess  2
//#define kEffectExplosion 3

#define kSceneGame		0
#define kSceneSettings	1
#define kSceneSplash	2

#define kVolTypeEffect	0
#define kVolTypeMusic	1


#endif
