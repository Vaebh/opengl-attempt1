//
//  TextureManager.h
//  OpenGL Attempt1
//
//  Created by Simon McDonnell on 07/08/2014.
//  Copyright (c) 2014 ___SimonMcDonnell___. All rights reserved.
//

#ifndef TEXTUREMANAGER_SIMEGINE
#define TEXTUREMANAGER_SIMEGINE

struct TextureData
{
	//TextureData(GLuint inTexID, float inWidth, float inHeight) {textureID = inTexID; width = inWidth; height = inHeight;}
	std::string name;
	GLuint textureID;
	float width;
	float height;
};

class TextureManager
{
    TextureManager();
    ~TextureManager();
    
    TextureData GetTexture();
    TextureData LoadTexture();
};

#endif
