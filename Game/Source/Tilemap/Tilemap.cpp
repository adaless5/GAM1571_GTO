#include "GamePCH.h"
#include "Tilemap.h"
#include "Base/Mesh.h"
#include "GameObjects/Camera.h"

Tilemap::Tilemap(char* filename)
{
    // Load JSON layout file.
    long fileLen;    
    char* fileContents = fw::LoadCompleteFile( filename, &fileLen );
    cJSON* jRoot = cJSON_Parse( fileContents );

    m_MapSize.x = cJSON_GetObjectItem( jRoot, "mapW" )->valueint;
    m_MapSize.y = cJSON_GetObjectItem( jRoot, "mapH" )->valueint;
    m_TileSize.x = (float)cJSON_GetObjectItem( jRoot, "tileW" )->valuedouble;
    m_TileSize.y = (float)cJSON_GetObjectItem( jRoot, "tileH" )->valuedouble;

    m_Layout = new TileType[m_MapSize.x * m_MapSize.y];

    cJSON* jLayout = cJSON_GetObjectItem( jRoot, "layout" );
    int sizeY = cJSON_GetArraySize( jLayout );
    assert( sizeY == m_MapSize.y );

    for( int y=0; y<sizeY; y++ )
    {
        cJSON* jRow = cJSON_GetArrayItem( jLayout, y );
        int sizeX = cJSON_GetArraySize( jRow );
        assert( sizeX == m_MapSize.x );

        for( int x=0; x<sizeX; x++ )
        {
            TileType type = (TileType)cJSON_GetArrayItem( jRow, x )->valueint;

            int index = (m_MapSize.y-1 - y) * m_MapSize.x + x;
            m_Layout[index] = type;
        }
    }

    delete[] fileContents;

    m_pMesh = new Mesh();
    m_pMesh->GenerateSquare( m_TileSize.x );

    m_pBuildingMesh = new Mesh();
    m_pBuildingMesh->GenerateBuilding( m_TileSize.x );

    m_pShader = new fw::ShaderProgram( "Data/Shaders/texture.vert", "Data/Shaders/texture.frag" );
    m_pBuildingShader = new fw::ShaderProgram( "Data/Shaders/building.vert", "Data/Shaders/building.frag" );

    // Create properties.
    m_Props = new TileProperties[(int)TileType::NumTypes];
    m_Props[(int)TileType::Road4].m_pMesh = m_pMesh;
    m_Props[(int)TileType::Road4].m_pShader = m_pShader;
    m_Props[(int)TileType::Road4].m_TextureID = fw::LoadTexture( "Data/Textures/Road4.png" );
    m_Props[(int)TileType::Road4].m_IsWalkable = true;
    m_Props[(int)TileType::Road4].m_IsSwimmable = false;

    m_Props[(int)TileType::Road2UD].m_pMesh = m_pMesh;
    m_Props[(int)TileType::Road2UD].m_pShader = m_pShader;
    m_Props[(int)TileType::Road2UD].m_TextureID = fw::LoadTexture( "Data/Textures/Road2UD.png" );
    m_Props[(int)TileType::Road2UD].m_IsWalkable = true;
    m_Props[(int)TileType::Road2UD].m_IsSwimmable = false;

    m_Props[(int)TileType::Road2LR].m_pMesh = m_pMesh;
    m_Props[(int)TileType::Road2LR].m_pShader = m_pShader;
    m_Props[(int)TileType::Road2LR].m_TextureID = fw::LoadTexture( "Data/Textures/Road2LR.png" );
    m_Props[(int)TileType::Road2LR].m_IsWalkable = true;
    m_Props[(int)TileType::Road2LR].m_IsSwimmable = false;

    m_Props[(int)TileType::Building].m_pMesh = m_pBuildingMesh;
    m_Props[(int)TileType::Building].m_pShader = m_pBuildingShader;
    m_Props[(int)TileType::Building].m_TextureID = fw::LoadTexture( "Data/Textures/Building.png" );
    m_Props[(int)TileType::Building].m_IsWalkable = false;
    m_Props[(int)TileType::Building].m_IsSwimmable = false;

    m_Props[(int)TileType::Water].m_pMesh = m_pMesh;
    m_Props[(int)TileType::Water].m_pShader = m_pShader;
    m_Props[(int)TileType::Water].m_TextureID = fw::LoadTexture( "Data/Textures/Water.png" );
    m_Props[(int)TileType::Water].m_IsWalkable = true;
    m_Props[(int)TileType::Water].m_IsSwimmable = true; 
}

Tilemap::~Tilemap()
{
    for( int i=0; i<(int)TileType::NumTypes; i++ )
    {
        glDeleteTextures( 1, &m_Props[i].m_TextureID );
    }

    delete m_pMesh;
    delete m_pBuildingMesh;
    delete m_pShader;
    delete m_pBuildingShader;

    delete[] m_Props;
    delete[] m_Layout;
}

void Tilemap::Draw(Camera* pCamera)
{
    for( int y=0; y<m_MapSize.y; y++ )
    {
        for( int x=0; x<m_MapSize.x; x++ )
        {
            int tileIndex = y * m_MapSize.x + x;
            TileType type = m_Layout[tileIndex];
            TileProperties* pProp = &m_Props[(int)type];

            vec2 pos( x * m_TileSize.x, y * m_TileSize.y );

            pProp->m_pMesh->Draw( pCamera, pProp->m_pShader, pos, pProp->m_TextureID );
        }
    }
}

bool Tilemap::IsTileWalkable(vec2 worldPos)
{
    int tx = (int)(worldPos.x / m_TileSize.x);
    int ty = (int)(worldPos.y / m_TileSize.y);

    if( tx < 0 || tx >= m_MapSize.x ) return false;
    if( ty < 0 || ty >= m_MapSize.y ) return false;

    int tileIndex = ty * m_MapSize.x + tx;
    TileType type = m_Layout[tileIndex];
    return m_Props[(int)type].m_IsWalkable;
}

bool Tilemap::IsTileSwimmable(vec2 worldPos)
{
    int tx = (int)(worldPos.x / m_TileSize.x);
    int ty = (int)(worldPos.y / m_TileSize.y);

    if (tx < 0 || tx >= m_MapSize.x) return false;
    if (ty < 0 || ty >= m_MapSize.y) return false;

    int tileIndex = ty * m_MapSize.x + tx;
    TileType type = m_Layout[tileIndex];
    return m_Props[(int)type].m_IsSwimmable;
}
