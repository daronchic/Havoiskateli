#include "stdafx.h"
#include "Level.h"
#include "tinyxml2.h"

#include <sstream>

using namespace tinyxml2;

Level::Level()
{
}

Level::Level(std::string mapName, Vector2 spawnPoint) :
	m_mapName(mapName),
	m_spawnPoint(spawnPoint),
	m_size(Vector2(0,0))
{
	this->loadMap(mapName);
}


Level::~Level()
{
}

void Level::moveDown()
{

}

void Level::moveLeft()
{

}

void Level::moveRight()
{

}

void Level::moveUp()
{

}

void Level::loadMap(std::string mapName) //mapName like stagefolder/level_name
{
	XMLDocument doc;
	std::stringstream ss;
	ss << "content/levels/" << mapName << ".tmx";
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->m_size = Vector2(width, height);

	int tileWidth, tileHeight;
	mapNode->QueryIntAttribute("tilewidth", &tileWidth);
	mapNode->QueryIntAttribute("tileheight", &tileHeight);
	this->m_tileSize = Vector2(tileWidth, tileHeight);

	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL) {


		while (pTileset) {
			int firstGid;
			std::stringstream sstr;
			std::stringstream tileSetFileName;
			std::string string;
			sstr.str("");
			tileSetFileName.str("");
			sstr.flush();
			tileSetFileName.flush();
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");
			sstr << source;
			
			sstr >> string;
			string.replace(string.begin(), string.begin()+6, "");
			tileSetFileName << "content/" << string;
			pTileset->QueryIntAttribute("firstgid", &firstGid);
			sf::Image* image = new sf::Image();
			image->loadFromFile(tileSetFileName.str());
			this->m_tilesets.push_back(Tileset(image, firstGid));

			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL) {
		while (pLayer) {
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) {
				while (pData) {
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						int tileCounter = 0;
						while (pTile) {
							if (pTile->IntAttribute("gid") == 0) {
								tileCounter++;
								//Continue
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
								//
							}

							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (int i = 0; i < this->m_tilesets.size(); i++) {
								if (this->m_tilesets[i].FirstGid <= gid) {
									tls = this->m_tilesets.at(i);
									break;
								}
							}

							if (tls.FirstGid == -1) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else {
									break;
								}
							}

							int xx = 0;
							int yy = 0;
							xx = tileCounter % width;
							xx *= tileWidth;
							yy = tileHeight * (tileCounter / width);
							Vector2 finalTilePosition = Vector2(xx, yy);

							int tilesetWidth = tls.Image->getSize().x;
							int tilesetHeight = tls.Image->getSize().y;
							int tilesetxx = gid % (tilesetWidth / tileWidth) - 1;
							tilesetxx *= tileWidth;
							int tilesetyy = 0;
							int amt = (gid / (tilesetWidth / tileWidth));
							tilesetyy = tileHeight * amt;
							Vector2 finalTilesetPosition = Vector2(tilesetxx, tilesetyy);
							Tile tile(tls.Image, Vector2(tileWidth, tileHeight), finalTilesetPosition, finalTilePosition);
							this->m_tileList.push_back(tile);
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}
					pData = pData->NextSiblingElement("data");
				}
			}
			pLayer = pLayer->NextSiblingElement("layer");
		}
	}
	m_levelTexture.create(1600, 1600);
	m_levelSprite.setTexture(m_levelTexture.getTexture());
}

void Level::update(float elapsedTime)
{
	m_levelSprite.move(m_dx * elapsedTime, m_dy * elapsedTime);
	if ((m_levelSprite.getPosition().x + m_levelSprite.getTexture()->getSize().x) < 800) {

		m_levelSprite.setPosition((800 - m_size.x), m_levelSprite.getPosition().y);
	}
	if ((m_levelSprite.getPosition().y + m_levelSprite.getTexture()->getSize().y) < 600) {
		m_levelSprite.setPosition(m_levelSprite.getPosition().x, 600 - m_size.y);
	}
}

void Level::draw(sf::RenderWindow &window)
{
	for each (auto tile in this->m_tileList)
	{
		tile.draw(m_levelTexture);
	}
	window.draw(m_levelSprite);
	m_levelTexture.display();
}
