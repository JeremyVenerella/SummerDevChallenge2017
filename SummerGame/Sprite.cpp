#include "Sprite.h"
#include "Vert.h"
#include "AssetManager.h"
#include <cstddef>



Sprite::Sprite()
{
	_vboID = 0;
}


Sprite::~Sprite()
{
	if (_vboID != 0)
	{
		glDeleteBuffers(1, &_vboID);
	}
}

void Sprite::init(float x, float y, float width, float height, std::string tPath)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	_texture = AssetManager::getTexture(tPath);

	if (_vboID == 0)
	{
		glGenBuffers(1, &_vboID);
	}

	Vertex vertexD[6];
	/////////////////////////////////////////
	vertexD[0].setPos(x + width, y + height);
	vertexD[0].setUV(1.0f, 1.0f);

	vertexD[1].setPos(x, y + height);
	vertexD[1].setUV(0.0f, 1.0f);

	vertexD[2].setPos(x, y);
	vertexD[2].setUV(0.0f, 0.0f);

	vertexD[3].setPos(x, y);
	vertexD[3].setUV(0.0f, 0.0f);

	vertexD[4].setPos(x + width, y);
	vertexD[4].setUV(1.0f, 0.0f);

	vertexD[5].setPos(x + width, y + height);
	vertexD[5].setUV(1.0f, 1.0f);
	/////////////////////////////////////////
	for (int i = 0; i < 6; i++)
	{
		//vertexD[i].setColor(255, 0, 255, 255);
	}
	//vertexD[1].setColor(0, 0, 255, 255);



	glBindBuffer(GL_ARRAY_BUFFER, _vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexD), vertexD, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, _texture.id);//No need to unbind textures
	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glEnableVertexAttribArray(0);

	//possition /color/ UV
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
