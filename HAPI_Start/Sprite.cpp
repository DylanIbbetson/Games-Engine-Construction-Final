#include "Sprite.h"
#include "Rectangle.h"


Sprite::Sprite(int maxFrames)
{

	m_maxFrames = maxFrames;

}

Sprite::~Sprite()
{
	delete m_texture;

}

bool Sprite::Load(const std::string& filename)
{
	//Error handling for missing textures
	if (!HAPI.LoadTexture(filename, &m_texture, m_textureWidth, m_textureHeight))
	{
		HAPI.UserMessage("Missing Texture", "Error");
		return false;
	}

	//Setting the frame width using the max frames and texture width
	if (m_maxFrames > 0)
	{
		m_frameWidth = m_textureWidth / m_maxFrames;
	}
	else if (m_maxFrames == 0)
	{
		m_frameWidth = m_textureWidth;
	}

	return true;
}

void Sprite::Render(BYTE* m_screen, int m_screenWidth, int m_screenHeight, int posX, int posY, bool m_alpha)
{
	if (!m_alpha)
	{
		//temporary pointers for the background texture and the screen
		BYTE* tempBackground{ m_texture };
		BYTE* tempScreen{ m_screen + (posX + posY * (size_t)m_screenWidth) * 4 };

		for (int i = 0; i < m_textureHeight; i++)
		{
			memcpy(tempScreen, tempBackground, (size_t)m_textureWidth * 4);
			tempBackground += (size_t)m_textureWidth * 4;
			tempScreen += (size_t)m_screenWidth * 4;
		}
	}
}

void Sprite::Clip(BYTE* m_screen, const Rectangle& screenRectangle, const Rectangle& textureRectangle, int posX, int posY, int currentFrame)
{

	//Clipping function that translates the clipped rectangles 
	Rectangle clippedRectangle(textureRectangle);

	clippedRectangle.Translate(posX, posY);

	clippedRectangle.ClipTo(screenRectangle);

	clippedRectangle.Translate(-posX, -posY);

	if (posX < 0)
	{
		posX = 0;
	}
	if (posY < 0)
	{
		posY = 0;
	}

	//Setting tempory pointers for the texture and the screen
	//BYTE* tempTexture{ m_texture + ((size_t)clippedRectangle.left + (size_t)clippedRectangle.top * textureRectangle.Width()) + ((size_t)currentFrame * m_frameWidth) * 4};
	BYTE* tempTexture{ m_texture + (((size_t)clippedRectangle.left + ((size_t)clippedRectangle.top * m_textureWidth) + ((size_t)currentFrame * m_frameWidth)) * 4) };

	BYTE* tempScreen{ m_screen + ((size_t)posX + (size_t)posY * screenRectangle.Width()) * 4 };

	int EndOfLineScreenOffset = (screenRectangle.Width() - clippedRectangle.Width()) * 4;
	int EndOfLineTextureOffset = (m_textureWidth - clippedRectangle.Width()) * 4;

	for (int y = 0; y < clippedRectangle.Height(); y++)
	{
		for (int x = 0; x < clippedRectangle.Width(); x++)
		{
			BYTE A = tempTexture[3];
			if (A == 255)
			{
				memcpy(tempScreen, tempTexture, 4);
			}
			else
			{
				//Storing the RGB values of the screen and the texture
				BYTE R = tempTexture[0];
				BYTE G = tempTexture[1];
				BYTE B = tempTexture[2];

				BYTE Rs = tempScreen[0];
				BYTE Gs = tempScreen[1];
				BYTE Bs = tempScreen[2];

				float alpha = A / 255.0f;

				tempScreen[0] = (BYTE)(alpha * R + (1.0f - alpha) * Rs);
				tempScreen[1] = (BYTE)(alpha * G + (1.0f - alpha) * Gs);
				tempScreen[2] = (BYTE)(alpha * B + (1.0f - alpha) * Bs);
			}
			tempTexture += 4;
			tempScreen += 4;
		}
		tempScreen += EndOfLineScreenOffset;
		tempTexture += EndOfLineTextureOffset;
	}
}
