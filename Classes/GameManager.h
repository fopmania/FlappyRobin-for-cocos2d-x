#pragma once
class GameManager
{
public:
	static GameManager* Instance();

    void Init();
    void Uninit();
    
	float GetScaleX();
	float GetScaleY();
	float GetScaleFactor();
	
	void SetUpScaleFactors();

	void GetFileName(char *array, const int len, const char*name, const char *fileExt);

	void LateInit();

//	void PlayEffect(const int num);
    void PlayEffect(const char* name);
	void RunScene(const int sceneNum);

	int GetVol(const int volType);
	void SetVol(const int volType, const int val);
	void StartBGMusic();
    void StopBGMusic();

	int GetHighScore();
	void SetHighScore(const int score);
    
    void SaveSettings(int volM, int volE);

private:
	GameManager() {};
	GameManager(GameManager const&) {};
	GameManager& operator=(GameManager const&) {};


//	void PreLoadEffect(const char* name, const int num);
//	void PlayEffectName(const char* name, const int num);

	static GameManager* _Instance;

	float scaleX;
	float scaleY;
	float scaleFactor;

	char *_ext;

	int _musicVol;
	int _effectsVol;
	int _highScore;

	~GameManager();
};


#define GETSCALEX ( GameManager::Instance()->GetScaleX())
#define GETSCALEY ( GameManager::Instance()->GetScaleY())
#define GETSCALEFAC ( (GETSCALEX+GETSCALEY)*0.5 )

#define SCALEX(p) ((p) * GETSCALEX)
#define SCALEY(p) ((p) * GETSCALEY)

#define SCALEPOS(x,y) ( Vec2 ( GETSCALEX * (x), GETSCALEY * (y) ))
#define SCALEFONT(p) ((p) * SCALEY )

#define GETFILENAME(a,l,n,e) \
	(GameManager::Instance()->GetFileName(a, l, n, e))

#define SCALENODE_XY(n) \
	n->setScaleX(GETSCALEX*kImageMulti); \
	n->setScaleY(GETSCALEY*kImageMulti)

#define SCALENODE_Y(n) \
    n->setScale(GETSCALEY);


#define SCALENODE_YM(n) \
    n->setScaleX(GETSCALEY*kImageMulti); \
    n->setScaleY(GETSCALEY*kImageMulti)


#define SCALENODE_X(n) \
    n->setScaleX(GETSCALEX);



