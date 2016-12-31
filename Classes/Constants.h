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
#define kRobinStartSpeedY 300 * GETSCALEY * GETSCALEFAC

#define GRAVITY -620 * GETSCALEY * GETSCALEFAC

#define kCloudScaleSlow 0.4 * GETSCALEY
#define kCloudScaleFast 0.85 * GETSCALEY
#define kMountScale 0.8 * GETSCALEY
#define kTreeScale 1.0 * GETSCALEY

#define kCloudSpeedSlow 13.0 * GETSCALEY * GETSCALEFAC
#define kCloudSpeedFast 53.0 * GETSCALEY * GETSCALEFAC
#define kMountSpeed 30.0 * GETSCALEY * GETSCALEFAC
#define kTreeSpeed  70.0 * GETSCALEY * GETSCALEFAC

#define kRobinStateMoving 0
#define kRobinStateStopped 1
#define kRobinStartSpeedY 300 * GETSCALEY * GETSCALEFAC

#define GRAVITY -620 * GETSCALEY * GETSCALEFAC

#define kTubeStateActive 0
#define kTubeStateInActive 1
#define kTubeInActiveX -1000 * GETSCALEX * GETSCALEFAC

#define kTubeSpawnMinTime 2.3
#define kTubeSpawnTimeVariance 8

#define kTubeTypeUpper 0
#define kTubeTypeLower 1
#define kTubeTypePair 2
#define kTubeTypeNone 3

#define kSingleGapTop 440 * GETSCALEY * GETSCALEFAC
#define kSingleGapBottom 230 * GETSCALEY * GETSCALEFAC
#define kSingleGapMax 280 * GETSCALEY * GETSCALEFAC
#define kSingleGapMin 160 * GETSCALEY * GETSCALEFAC

#define kDoubleGapTop 480 * GETSCALEY * GETSCALEFAC
#define kDoubleGapBottom 120 * GETSCALEY * GETSCALEFAC
#define kDoubleGapMax 220 * GETSCALEY * GETSCALEFAC
#define kDoubleGapMin 140 * GETSCALEY * GETSCALEFAC

#define kTubeMaxUpPixels 180 * GETSCALEY * GETSCALEFAC

#define kFontName	"Marker Felt.ttf"

#define kFileBG			"BG-HD.png"
#define kFileFloor		"Floor-HD.png"
#define kFileRobin		"Robin-HD.png"
#define kFileCloud		"Cloud-HD.png"
#define kFileMount		"Mount-HD.png"
#define kFileTree		"Tree-HD.png"

#define kEffectRobinTap 0
#define kEffectSuccess 1
#define kEffectExplosion 2

#define kSceneGame		0
#define kSceneSettings	1
#define kSceneSplash	2

#define kVolTypeEffect	0
#define kVolTypeMusic	1


#endif