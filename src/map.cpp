#include "global.hpp"

extern State state;

Map::Map()
{
}

void Map::setup()
{
    loadMapInfo();
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

void Map::loadMapInfo()
{
    std::ifstream file("assets/map/map_info.json");
    if (!file.is_open())
    {
        std::cerr << "Failed to open JSON file." << std::endl;
        return;
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

    int width = -1;
    int height = -1;

    if (document.HasMember("width") && document["width"].IsInt() &&
        document.HasMember("height") && document["height"].IsInt())
    {
        width = document["width"].GetInt();
        height = document["height"].GetInt();
    }

    if (document.HasMember("layers") && document["layers"].IsArray())
    {
        const rapidjson::Value &layers = document["layers"];

        if (layers.Size() > 0)
        {
            const rapidjson::Value &layer = layers[0];
            if (layer.HasMember("data") && layer["data"].IsArray())
            {
                const rapidjson::Value &data = layer["data"];
                if (data.Size() > 0)
                {
                    int dataLength = data.Size();
                    int dataArray[dataLength];

                    for (int i = 0; i < dataLength; ++i)
                    {
                        dataArray[i] = data[i].GetInt();
                    }

                    int tileMap[height][width];

                    for (int i = 0; i < height; ++i)
                    {
                        for (int j = 0; j < width; ++j)
                        {
                            int dataIndex = i * width + j;
                            tileMap[i][j] = dataArray[dataIndex];
                        }
                    }

                    GRID_ROWS = height;
                    GRID_ROWS = width;

                    tileGrid.resize(GRID_ROWS, std::vector<Sprite>(GRID_COLS, Sprite()));

                    for (int i = 0; i < GRID_ROWS; ++i)
                    {
                        for (int j = 0; j < GRID_COLS; ++j)
                        {
                            tileGrid[i][j] = Sprite(textureTypeFromMapInfo(tileMap[i][j]), {j * 32.0f, i * 32.0f}, 32, 32);
                        }
                    }
                }
            }
        }
    }
}

TextureType Map::textureTypeFromMapInfo(int identifier)
{
    switch (identifier)
    {
    case 1:
        return TextureType::SKY;
    case 2:
        return TextureType::WATER;
    case 3:
        return TextureType::ROCK;
    case 4:
        return TextureType::SKY_LIGHT;
    default:
        return TextureType::NONE;
    }
}
