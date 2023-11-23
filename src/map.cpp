#include "global.hpp"

extern State state;

Map::Map()
{
}

bool Map::setup()
{
    std::ifstream file("assets/map/map_info.json");

    if (!file.is_open())
    {
        std::cerr << "Failed to open JSON file." << std::endl;
        return false;
    }

    std::string jsonContent;
    std::string line;

    while (std::getline(file, line))
    {
        jsonContent += line;
    }

    file.close();

    rapidjson::Document document;
    document.Parse(jsonContent.c_str());

    if (!document.HasMember("width") || !document["width"].IsInt() ||
        !document.HasMember("height") || !document["height"].IsInt())
    {
        std::cerr << "Height or Width is missing from JSON." << std::endl;
        return false;
    }

    int width = document["width"].GetInt();
    int height = document["height"].GetInt();

    if (!document.HasMember("layers") || !document["layers"].IsArray())
    {
        std::cerr << "Layers is missing from JSON." << std::endl;
        return false;
    }

    const rapidjson::Value &layers = document["layers"];

    if (layers.Size() == 0)
    {
        std::cerr << "Layers are empty." << std::endl;
        return false;
    }

    const rapidjson::Value &layer = layers[0];

    if (!layer.HasMember("data") || !layer["data"].IsArray())
    {
        std::cerr << "Data is missing from JSON." << std::endl;
        return false;
    }

    const rapidjson::Value &data = layer["data"];

    if (data.Size() == 0)
    {
        std::cerr << "Data is empty." << std::endl;
        return false;
    }

    int dataLength = data.Size();
    int *dataArray = new int[dataLength];

    for (int i = 0; i < dataLength; ++i)
    {
        dataArray[i] = data[i].GetInt();
    }

    int **tileMap = new int *[height];
    for (int i = 0; i < height; ++i)
    {
        tileMap[i] = new int[width];
    }

    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            int dataIndex = i * width + j;
            tileMap[i][j] = dataArray[dataIndex];
        }
    }

    GRID_ROWS = height;
    GRID_COLS = width;

    tileGrid.resize(GRID_ROWS, std::vector<Tile>(GRID_COLS, Tile()));

    if (!document.HasMember("tilesets") || !document["tilesets"].IsArray())
    {
        std::cerr << "TileSets is missing from JSON." << std::endl;
        return false;
    }

    const rapidjson::Value &tilesets = document["tilesets"];

    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {
            int type = tileMap[i][j];

            std::string source = tilesets[type - 1]["source"].GetString();
            size_t dotPosition = source.find('.');
            source.replace(dotPosition, std::string::npos, ".png");

            SDL_Surface *surface = IMG_Load(("assets/textures/" + source).c_str());
            SDL_Texture *texture = SDL_CreateTextureFromSurface(state.renderer, surface);
            SDL_FreeSurface(surface);
            TileType tileType = tileTypeFromName(source);
            SDL_FPoint position = {j * 32.0f, i * 32.0f};
            tileGrid[i][j] = Tile(tileType, texture, position);
        }
    }

    delete[] dataArray;

    for (int i = 0; i < height; ++i)
    {
        delete[] tileMap[i];
    }
    delete[] tileMap;

    return true;
}

void Map::update()
{
    std::vector<Particle> filteredParticles;

    auto lifeTimeExceeded = [](Particle particle)
    { return SDL_GetTicks() - particle.startLife < static_cast<Uint32>(particle.lifeTime); };

    std::copy_if(particles.begin(), particles.end(), std::back_inserter(filteredParticles), lifeTimeExceeded);

    particles = filteredParticles;

    for (size_t i = 0; i < particles.size(); i++)
    {
        particles[i].update();
    }
}

void Map::render()
{
    for (int i = 0; i < GRID_ROWS; ++i)
    {
        for (int j = 0; j < GRID_COLS; ++j)
        {
            tileGrid[i][j].render();
        }
    }

    for (size_t i = 0; i < particles.size(); i++)
    {
        particles[i].render();
    }
}

void Map::createParticle(Particle _particle)
{
    particles.push_back(_particle);
}

TileType Map::tileTypeFromName(std::string name)
{
    if (name.find("rock") != std::string::npos)
    {
        return TileType::SOLID;
    }
    if (name.find("water") != std::string::npos)
    {
        return TileType::WATER;
    }

    return TileType::NON_SOLID;
}
