#ifndef _CSCENE_H_
#define _CSCENE_H_

class CInput;

// Class name: CScene //
class CScene
{
private:

public:
	CScene();
	CScene(const CScene&);
	~CScene();

	virtual void Initialize();
	virtual void Shutdown();

	virtual void Update(CInput*);
	virtual void Render();
};
#endif