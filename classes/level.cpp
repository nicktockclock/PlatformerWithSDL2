#include "level.h"
#include "graphics.h"
#include <SDL2/SDL.h>
#include "globals.h"
#include <tinyxml2.h>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <utils.h>
#include "../include/tileson.h"
#include "../include/tileson_parser.hpp"

Level::Level(){}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics):
    _mapName(mapName),
    _spawnPoint(spawnPoint),
    _size(Vector2(0, 0))
{
    loadMap(mapName, graphics);
}

Level::~Level(){}

void Level::loadMap(std::string mapName, Graphics &graphics){
    //Parse the .tmx file
    tson::Tileson parser;
    
    std::stringstream ss;
    ss << "content/maps/" << mapName << ".json";
    std::unique_ptr<tson::Map> tiled_map = parser.parse(ss.str());
    if(tiled_map->getStatus() == tson::ParseStatus::FileNotFound){
        printf("heyeyeye\n");
    }
    auto map_dimensions = tiled_map->getSize(); 
    auto tilesize = tiled_map->getTileSize();
    printf(ss.str().c_str());
    //Get the width and height of the map and store it in _size;
    int width, height;
    width = map_dimensions.x;
    height = map_dimensions.y;
    _size = Vector2(width, height);

    //Get the width and height of the tiles and store it in _tileSize
    int tileWidth, tileHeight;
    tileWidth = tilesize.x;
    tileHeight = tilesize.y;
    _tileSize = Vector2(tileWidth, tileHeight);

    //Load the tilesets
    auto& map_tilesets = tiled_map->getTilesets();
    for (auto& tset: map_tilesets){
        std::stringstream ssts;
        int firstGid = tset.getFirstgid();
        ssts << "content";
        for (int i = 2; i < tset.getImagePath().string().size(); i++) {
            ssts << tset.getImagePath().string().at(i);
        }
        
        SDL_Texture* tex = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ssts.str()));
        _tilesets.push_back(Tileset(tex, firstGid));
    }

    //Load the layers
    auto& map_layers = tiled_map->getLayers();
    for (auto& layer : map_layers){
        std::cout << layer.getName() << std::endl;
        if (layer.getName() == "Background" || layer.getName() == "Foreground") {
            // Grab all of this layer's tiles. 
            auto& layer_tiles = layer.getTileData();
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    auto tile = layer.getTileData(j, i);
                    
                    if (tile == nullptr) {
                        continue;
                    }
                    auto cur_gid = tile->getId();

                    // Find the tileset that this tile belongs to. The tileset
                    // whose first GID is less-than-or-equal to this GID, is
                    // the tileset our GID belongs to. A tileset with a first
                    // GID that is greater than this tile means that this tile
                    // does not belong to that tileset.
                    auto tset_gid = -1;
                    Tileset tset_used;
                    for (auto& ts : _tilesets) {
                        if (ts.FirstGid <= cur_gid) {
                            tset_gid = ts.FirstGid;
                            tset_used = ts;
                            break;
                        }
                    }
                    //Skip if we didn't find a matching tileset
                    if (tset_gid == -1) {
                        continue;
                    }
                    
                    // Normalize the GID.
                    cur_gid -= tset_gid;

                    // Find the dimensions of the tile sheet.
                    auto ts_width = 0;
                    auto ts_height = 0;
                    SDL_QueryTexture(tset_used.Texture,
                        NULL, NULL, &ts_width, &ts_height);

                    // Calculate the area on the tilesheet to draw from.
                    auto region_x = (cur_gid % (ts_width / tileWidth)) * tileWidth;
                    auto region_y = (cur_gid / (ts_width / tileWidth)) * tileHeight;

                    // Calculate the world position of our tile. This is easy,
                    // because we're using nested for-loop to visit each x,y
                    // coordinate.
                    auto x_pos = j * tileWidth;
                    auto y_pos = i * tileHeight;

                    Tile t = Tile(tset_used.Texture, Vector2(tileWidth, tileHeight), 
                        Vector2(region_x, region_y), Vector2(x_pos, y_pos));
                    _tilelist.push_back(t);

                }
            }
        }
        else if (layer.getName() == "Slopes"){
            for (auto &object : layer.getObjects()){
                Vector2 p1;
                p1 = Vector2(std::ceil(object.getPosition().x), std::ceil(object.getPosition().y));

                std::vector<tson::Vector2i> pPolyline = object.getPolylines();
                if (!pPolyline.empty()){
                    //Now to turn the points into slopes
                    for (int i = 0; i < pPolyline.size()-1; i++){
                        _slopes.push_back(Slope(
                            Vector2((p1.x + pPolyline.at(i).x) * globals::SPRITE_SCALE, 
                                    (p1.y + pPolyline.at(i).y) * globals::SPRITE_SCALE), 
                            Vector2((p1.x + pPolyline.at(i+1).x) * globals::SPRITE_SCALE, 
                                    (p1.y + pPolyline.at(i+1).y) * globals::SPRITE_SCALE)));
                    }
                }                   
            }
        }
        else if (layer.getName() == "Collisions"){
            for (auto &object : layer.getObjects()){
                float x, y, width, height;
                x = object.getPosition().x;
                y = object.getPosition().y;
                width = object.getSize().x;
                height = object.getSize().y;
                _collisionRects.push_back(Rectangle(
                    std::ceil(x) * globals::SPRITE_SCALE,
                    std::ceil(y) * globals::SPRITE_SCALE,
                    std::ceil(width) * globals::SPRITE_SCALE,
                    std::ceil(height) * globals::SPRITE_SCALE
                ));
            }
        }
        else if (layer.getName() == "SpawnPoints"){
            for (auto &object : layer.getObjects()){
                float x = object.getPosition().x;
                float y = object.getPosition().y;
                if (object.getName() == "Player"){
                    _spawnPoint = Vector2(std::ceil(x) * globals::SPRITE_SCALE,
                        std::ceil(y) * globals::SPRITE_SCALE);
                }
            }
        }          
    }
}



void Level::update(int elapsedTime){

}

void Level::draw(Graphics &graphics){
    for (int i = 0; i < _tilelist.size(); i++){
        _tilelist.at(i).draw(graphics);
    }
}

std::vector<Rectangle> Level::checkTileCollisions(const Rectangle &other){
    std::vector<Rectangle> others;
    for (int i = 0; i < _collisionRects.size(); i++){
        if (_collisionRects.at(i).collidesWith(other)){
            others.push_back(_collisionRects.at(i));
        }
    }
    return others;
}

std::vector<Slope> Level::checkSlopeCollisions(const Rectangle &other){
    std::vector<Slope> others;
    for (int i = 0; i < _slopes.size(); i++){
        if (_slopes.at(i).collidesWith(other)){
            others.push_back(_slopes.at(i));
        }
    }
    return others;
}

const Vector2 Level::getPlayerSpawnPoint() const{
    return _spawnPoint;
}