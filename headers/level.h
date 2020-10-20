#ifndef LEVEL_H
#define LEVEL_H

#include "globals.h"
#include <string>
#include "tile.h"
#include <vector>
#include "rectangle.h"
#include "slope.h"

class Graphics;
struct SDL_Texture;
struct SDL_Rect;
struct Tileset;

class Level{
    public:
        Level();
        Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
        ~Level();
        void update(int elapsedTime);
        void draw(Graphics &graphics);

        //std::vector<Rectangle> checkTileCollisions
        //Go through tiles and find any that are colliding with the given rectangle
        std::vector<Rectangle> checkTileCollisions(const Rectangle &other);
        std::vector<Slope> checkSlopeCollisions(const Rectangle &other);

        const Vector2 getPlayerSpawnPoint() const;

    private:
        std::string _mapName;
        Vector2 _spawnPoint;
        Vector2 _size;
        Vector2 _tileSize;

        SDL_Texture* _backgroundTexture;

        std::vector<Tile> _tilelist;
        std::vector<Tileset> _tilesets;
        std::vector<Rectangle> _collisionRects;
        std::vector<Slope> _slopes;


        /* void loadMap
        * This loads a map
        */
        void loadMap(std::string mapName, Graphics &graphics);
        

};

//Tileset struct
struct Tileset{
    SDL_Texture* Texture;
    int FirstGid;

    Tileset(){
        FirstGid = -1;
    }

    Tileset(SDL_Texture* texture, int firstGid){
        Texture = texture;
        FirstGid = firstGid;
    }
};

#endif