/*
 * Group.cpp
 *
 *  Created on: 29/03/2017
 *      Author: bpereira
 */

#include "Group.h"
#include <sstream>
#include <map>
#include <vector>

#include "Constantes.h"
#include "MatDiffuse.h"
#include "MatEmissive.h"
#include "MatSpecular.h"
#include "MatAmbient.h"

#include "LightDiffuse.h"

#include "LightSpecular.h"
#include "LightAmbient.h"

#include "Spotlight.h"
#include "FixedLight.h"
#include "DirectionalLight.h"





int loadTexture ( std::string s )
{   unsigned int t, tw, th;
    unsigned char *texData;
    unsigned int texID;
    ilInit();
    ilEnable ( IL_ORIGIN_SET );
    ilOriginFunc ( IL_ORIGIN_LOWER_LEFT );
    ilGenImages ( 1, &t );
    ilBindImage ( t );
    ilLoadImage ( ( ILstring ) s.c_str() );
    tw = ilGetInteger ( IL_IMAGE_WIDTH );
    th = ilGetInteger ( IL_IMAGE_HEIGHT );
    ilConvertImage ( IL_RGBA, IL_UNSIGNED_BYTE );
    texData = ilGetData();
    glGenTextures ( 1, &texID );
    glBindTexture ( GL_TEXTURE_2D, texID );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                      GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                      GL_LINEAR_MIPMAP_LINEAR );
    glTexImage2D ( GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, texData );
    glGenerateMipmap ( GL_TEXTURE_2D );
    glBindTexture ( GL_TEXTURE_2D, 0 );
    return texID;
}

void initBuffers ( Models *models, VBO vbo, vector<float> points,
                   vector<float> normals, vector<float> textCoords )
{   float *a = &points[0];
    /**
     * Buffer Initialization
     */
    glEnableClientState ( GL_VERTEX_ARRAY );
    glGenBuffers ( 1, &models->buffers[vbo.index] );
    glBindBuffer ( GL_ARRAY_BUFFER, models->buffers[vbo.index] );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( float ) * vbo.size * 3, &points[0],
                   GL_STATIC_DRAW );
    glGenBuffers ( 1, &models->normals[vbo.index] );
    glBindBuffer ( GL_ARRAY_BUFFER, models->normals[vbo.index] );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( float ) * vbo.size * 3, &normals[0],
                   GL_STATIC_DRAW );
    glGenBuffers ( 1, &models->textCoords[vbo.index] );
    glBindBuffer ( GL_ARRAY_BUFFER, models->textCoords[vbo.index] );
    glBufferData ( GL_ARRAY_BUFFER, sizeof ( float ) * vbo.size * 2, &textCoords[0],
                   GL_STATIC_DRAW );
}

void drawVBO ( Models *models, VBO vbo )
{   /**
     * VBOs - Drawing
     */
    glBindBuffer ( GL_ARRAY_BUFFER, models->buffers[vbo.index] );
    glVertexPointer ( 3, GL_FLOAT, 0, 0 );
    glBindBuffer ( GL_ARRAY_BUFFER, models->normals[vbo.index] );
    glNormalPointer ( GL_FLOAT, 0, 0 );
    glBindBuffer ( GL_ARRAY_BUFFER, models->textCoords[vbo.index] );
    glTexCoordPointer ( 2, GL_FLOAT, 0, 0 );
    glDrawArrays ( GL_TRIANGLES, 0, vbo.size );
}

void drawElement ( Models *models, Group *g )
{   for ( int i = 0; i < g->models.size(); ++i )
    {   for ( auto material : g->materials.at ( i ) )
        {   material->applyProperties();
        }

        auto entry = models->figures.find ( g->models.at ( i ) );
        auto entry_texture = models->textures.find ( g->textures.at ( i ) );

        if ( entry != models->figures.end() )
        {   if ( entry_texture != models->textures.end() )
            {   glBindTexture ( GL_TEXTURE_2D, entry_texture->second );
            }

            drawVBO ( models, entry->second );
            glBindTexture ( GL_TEXTURE_2D, 0 );
        }

        for ( auto material : models->materials_defaults )
        {   material->applyProperties();
        }
    }
}

void readFile ( Models *models, string file )
{   auto entry = models->figures.find ( file );

    if ( entry == models->figures.end() )
    {   string line;
        vector<float> lstPts;
        vector<float> lstNrms;
        vector<float> lstTxts;
        VBO vbo;
        vbo.size = 0;
        ifstream myfile ( "resources/" + file, ios::in );

        if ( myfile.is_open() )
        {   while ( getline ( myfile, line ) )
            {   std::stringstream is ( line );
                float x, y, z, nx, ny, nz, tx, ty;
                is >> x;
                is >> y;
                is >> z;
                is >> nx;
                is >> ny;
                is >> nz;
                is >> tx;
                is >> ty;
                lstPts.push_back ( x );
                lstPts.push_back ( y );
                lstPts.push_back ( z );
                lstNrms.push_back ( nx );
                lstNrms.push_back ( ny );
                lstNrms.push_back ( nz );
                lstTxts.push_back ( tx );
                lstTxts.push_back ( ty );
                vbo.size++;
            }

            myfile.close();
            vbo.index = models->n_buffers;
            models->buffers.push_back ( 0 );
            models->normals.push_back ( 0 );
            models->textCoords.push_back ( 0 );
            models->figures.insert ( std::pair<string, VBO> ( file, vbo ) );
            initBuffers ( models, vbo, lstPts, lstNrms, lstTxts );
            models->n_buffers++;
        }

        else
            cout << "Unable to open file";
    }
}

void readXMLFromRootElement ( XMLElement *element, Models *models,
                              Group *group )
{   if ( element == nullptr )
        return;

    /**
     * Para cada irmão do elemento inicial: procurar atributos
     */
    for ( element = element->FirstChildElement(); element;
            element = element->NextSiblingElement() )
    {   string name ( element->Name() );
        Transformation *tr = 0;

        if ( ( name.compare ( TRANSLATE ) == 0 ) || ( name.compare ( SCALE ) == 0 ) )
        {   float x, y, z;

            if ( name.compare ( TRANSLATE ) == 0 )
            {   if ( element->Attribute ( TIME ) )
                {   float time = atof ( element->Attribute ( TIME ) );
                    AnimatedTranslation *at = new AnimatedTranslation ( time );

                    for ( auto crawlPoint = element->FirstChildElement ( POINT );
                            crawlPoint != nullptr;
                            crawlPoint = crawlPoint->NextSiblingElement (
                                             POINT ) )
                    {   x = ( crawlPoint->Attribute ( X ) ) ?
                            atof ( crawlPoint->Attribute ( X ) ) : 0;
                        y = ( crawlPoint->Attribute ( Y ) ) ?
                            atof ( crawlPoint->Attribute ( Y ) ) : 0;
                        z = ( crawlPoint->Attribute ( Z ) ) ?
                            atof ( crawlPoint->Attribute ( Z ) ) : 0;
                        at->addPointCoords ( x, y, z );
                    }

                    group->transformations.push_back ( at );
                }

                else
                {   x = ( element->Attribute ( X ) ) ?
                        atof ( element->Attribute ( X ) ) : 0;
                    y = ( element->Attribute ( Y ) ) ?
                        atof ( element->Attribute ( Y ) ) : 0;
                    z = ( element->Attribute ( Z ) ) ?
                        atof ( element->Attribute ( Z ) ) : 0;
                    /**
                     * Criar Translação
                     */
                    Translation *t = new Translation ( x, y, z );
                    group->transformations.push_back ( t );
                }
            }

            else
            {   x = ( element->Attribute ( X ) ) ? atof ( element->Attribute ( X ) ) : 0;
                y = ( element->Attribute ( Y ) ) ? atof ( element->Attribute ( Y ) ) : 0;
                z = ( element->Attribute ( Z ) ) ? atof ( element->Attribute ( Z ) ) : 0;
                /**
                 * Criar Escala
                 */
                Scale *s = new Scale ( x, y, z );
                group->transformations.push_back ( s );
            }
        }

        else if ( name.compare ( ROTATE ) == 0 )
        {   float axis_x, axis_y, axis_z, angle;

            if ( element->Attribute ( TIME ) )
            {   float time = atof ( element->Attribute ( TIME ) );
                axis_x =
                    ( element->Attribute ( AXIS_X ) ) ?
                    atof ( element->Attribute ( AXIS_X ) ) : 0;
                axis_y =
                    ( element->Attribute ( AXIS_Y ) ) ?
                    atof ( element->Attribute ( AXIS_Y ) ) : 0;
                axis_z =
                    ( element->Attribute ( AXIS_Z ) ) ?
                    atof ( element->Attribute ( AXIS_Z ) ) : 0;
                AnimatedRotation *ar = new AnimatedRotation ( time, axis_x,
                        axis_y, axis_z );
                group->transformations.push_back ( ar );
            }

            else
            {   angle = ( element->Attribute ( ANGLE ) ) ?
                        atof ( element->Attribute ( ANGLE ) ) : 0;
                axis_x =
                    ( element->Attribute ( AXIS_X ) ) ?
                    atof ( element->Attribute ( AXIS_X ) ) : 0;
                axis_y =
                    ( element->Attribute ( AXIS_Y ) ) ?
                    atof ( element->Attribute ( AXIS_Y ) ) : 0;
                axis_z =
                    ( element->Attribute ( AXIS_Z ) ) ?
                    atof ( element->Attribute ( AXIS_Z ) ) : 0;
                /**
                 * Criar Rotação
                 */
                Rotation *r = new Rotation ( angle, axis_x, axis_y, axis_z );
                group->transformations.push_back ( r );
            }
        }

        else if ( name.compare ( MODELS ) == 0 )
        {   /**
             * Iterar sobre os ficheiros de modelos
             */
            for ( auto crawl = element->FirstChildElement ( MODEL );
                    crawl != nullptr;
                    crawl = crawl->NextSiblingElement ( MODEL ) )
            {   string model ( crawl->Attribute ( FILE_D ) );
                string texture ( "" );

                if ( crawl->Attribute ( TEXTURE ) )
                    texture.append ( crawl->Attribute ( TEXTURE ) );

                vector<Materials *> matrls;

                for ( auto material = crawl->FirstChildElement(); material;
                        material = material->NextSiblingElement() )
                {   string property ( material->Name() );
                    float r, g, b, shin;

                    if ( property.compare ( DIFFUSE ) == 0 )
                    {   r = ( material->Attribute ( R ) ) ?
                            atof ( material->Attribute ( R ) ) : 0;
                        g = ( material->Attribute ( G ) ) ?
                            atof ( material->Attribute ( G ) ) : 0;
                        b = ( material->Attribute ( B ) ) ?
                            atof ( material->Attribute ( B ) ) : 0;
                        MatDiffuse *matD = new MatDiffuse ( r, g, b, 1.0f );
                        matrls.push_back ( matD );
                    }

                    else if ( property.compare ( SPECULAR ) == 0 )
                    {   r = ( material->Attribute ( R ) ) ?
                            atof ( material->Attribute ( R ) ) : 0;
                        g = ( material->Attribute ( G ) ) ?
                            atof ( material->Attribute ( G ) ) : 0;
                        b = ( material->Attribute ( B ) ) ?
                            atof ( material->Attribute ( B ) ) : 0;
                        shin = ( material->Attribute ( SHININESS ) ) ?
                               atof ( material->Attribute ( SHININESS ) ) : 0;
                        MatSpecular *matS = new MatSpecular ( r, g, b, 1.0f,
                                                              shin );
                        matrls.push_back ( matS );
                    }

                    else if ( property.compare ( AMBIENT ) == 0 )
                    {   r = ( material->Attribute ( R ) ) ?
                            atof ( material->Attribute ( R ) ) : 0;
                        g = ( material->Attribute ( G ) ) ?
                            atof ( material->Attribute ( G ) ) : 0;
                        b = ( material->Attribute ( B ) ) ?
                            atof ( material->Attribute ( B ) ) : 0;
                        MatAmbient *matA = new MatAmbient ( r, g, b, 1.0f );
                        matrls.push_back ( matA );
                    }

                    else if ( property.compare ( EMISSIVE ) == 0 )
                    {   r = ( material->Attribute ( R ) ) ?
                            atof ( material->Attribute ( R ) ) : 0;
                        g = ( material->Attribute ( G ) ) ?
                            atof ( material->Attribute ( G ) ) : 0;
                        b = ( material->Attribute ( B ) ) ?
                            atof ( material->Attribute ( B ) ) : 0;
                        MatEmissive *matE = new MatEmissive ( r, g, b, 0.0f );
                        matrls.push_back ( matE );
                    }
                }

                group->models.push_back ( model );
                group->materials.push_back ( matrls );
                group->textures.push_back ( texture );

                if ( texture.size() > 0 )
                {   string tmp ( "textures/" + texture );
                    GLuint texId = loadTexture ( tmp );
                    models->textures.insert (
                        std::pair<string, GLuint> ( texture, texId ) );
                }

                readFile ( models, model );
            }
        }

        else if ( name.compare ( LIGHTS ) == 0 )
        {   int i = 0;
            int light_n = GL_LIGHT0;

            for ( auto light = element->FirstChildElement ( LIGHT );
                    light != nullptr;
                    light = light->NextSiblingElement ( LIGHT ) )
            {   string light_type ( light->Attribute ( TYPE ) );
                float posX, posY, posZ, dirX, dirY, dirZ, const_at, lin_at,
                      quad_at, cutoff_angle, exponent;
                light_n += i;
                Light *lights = 0;

                if ( light_type.compare ( LIGHTDIR ) == 0 )
                {   posX = ( light->Attribute ( POS_X ) ) ?
                           atof ( light->Attribute ( POS_X ) ) : 0;
                    posY = ( light->Attribute ( POX_Y ) ) ?
                           atof ( light->Attribute ( POX_Y ) ) : 0;
                    posZ = ( light->Attribute ( POS_Z ) ) ?
                           atof ( light->Attribute ( POS_Z ) ) : 1;
                    lights = new DirectionalLight ( light_n,
                                                    posX, posY, posZ );
                }

                else if ( light_type.compare ( LIGHTPT ) == 0 )
                {   posX = ( light->Attribute ( POS_X ) ) ?
                           atof ( light->Attribute ( POS_X ) ) : 0;
                    posY = ( light->Attribute ( POX_Y ) ) ?
                           atof ( light->Attribute ( POX_Y ) ) : 0;
                    posZ = ( light->Attribute ( POS_Z ) ) ?
                           atof ( light->Attribute ( POS_Z ) ) : 1;
                    const_at =
                        ( light->Attribute ( CONST_AT ) ) ?
                        atof ( light->Attribute ( CONST_AT ) ) : 1;
                    lin_at =
                        ( light->Attribute ( LIN_AT ) ) ?
                        atof ( light->Attribute ( LIN_AT ) ) : 0;
                    quad_at =
                        ( light->Attribute ( QUAD_AT ) ) ?
                        atof ( light->Attribute ( QUAD_AT ) ) : 0;
                    lights = new FixedLight ( light_n, posX, posY,
                                              posZ, const_at, lin_at, quad_at );
                }

                else if ( light_type.compare ( SPOTLIGHT ) == 0 )
                {   posX = ( light->Attribute ( POS_X ) ) ?
                           atof ( light->Attribute ( POS_X ) ) : 0;
                    posY = ( light->Attribute ( POX_Y ) ) ?
                           atof ( light->Attribute ( POX_Y ) ) : 0;
                    posZ = ( light->Attribute ( POS_Z ) ) ?
                           atof ( light->Attribute ( POS_Z ) ) : 1;
                    dirX = ( light->Attribute ( DIR_X ) ) ?
                           atof ( light->Attribute ( DIR_X ) ) : 0;
                    dirY = ( light->Attribute ( DIR_Y ) ) ?
                           atof ( light->Attribute ( DIR_Y ) ) : 0;
                    dirZ = ( light->Attribute ( DIR_Z ) ) ?
                           atof ( light->Attribute ( DIR_Z ) ) : -1;
                    const_at =
                        ( light->Attribute ( CONST_AT ) ) ?
                        atof ( light->Attribute ( CONST_AT ) ) : 1;
                    lin_at =
                        ( light->Attribute ( LIN_AT ) ) ?
                        atof ( light->Attribute ( LIN_AT ) ) : 0;
                    quad_at =
                        ( light->Attribute ( QUAD_AT ) ) ?
                        atof ( light->Attribute ( QUAD_AT ) ) : 0;
                    cutoff_angle =
                        ( light->Attribute ( CUTOFF ) ) ?
                        atof ( light->Attribute ( CUTOFF ) ) : 180;
                    exponent =
                        ( light->Attribute ( EXPONENT ) ) ?
                        atof ( light->Attribute ( EXPONENT ) ) : 0;
                    lights = new Spotlight ( light_n, posX, posY,
                                             posZ, dirX, dirY, dirZ, cutoff_angle, const_at,
                                             lin_at, quad_at, exponent );
                }

                LightProperty *lt = 0;

                for ( auto crawl = light->FirstChildElement();
                        crawl != nullptr;
                        crawl = crawl->NextSiblingElement() )
                {   string property ( crawl->Name() );
                    float r, g, b, shin;

                    if ( property.compare ( DIFFUSE ) == 0 )
                    {   r = ( crawl->Attribute ( R ) ) ?
                            atof ( crawl->Attribute ( R ) ) : 0;
                        g = ( crawl->Attribute ( G ) ) ?
                            atof ( crawl->Attribute ( G ) ) : 0;
                        b = ( crawl->Attribute ( B ) ) ?
                            atof ( crawl->Attribute ( B ) ) : 0;
                        lt= new LightDiffuse ( light_n, r, g, b );
                    }

                    else if ( property.compare ( SPECULAR ) == 0 )
                    {   r = ( crawl->Attribute ( R ) ) ?
                            atof ( crawl->Attribute ( R ) ) : 0;
                        g = ( crawl->Attribute ( G ) ) ?
                            atof ( crawl->Attribute ( G ) ) : 0;
                        b = ( crawl->Attribute ( B ) ) ?
                            atof ( crawl->Attribute ( B ) ) : 0;
                        lt = new LightSpecular ( light_n, r, g,
                                                 b );
                    }

                    else if ( property.compare ( AMBIENT ) == 0 )
                    {   r = ( crawl->Attribute ( R ) ) ?
                            atof ( crawl->Attribute ( R ) ) : 0;
                        g = ( crawl->Attribute ( G ) ) ?
                            atof ( crawl->Attribute ( G ) ) : 0;
                        b = ( crawl->Attribute ( B ) ) ?
                            atof ( crawl->Attribute ( B ) ) : 0;
                        lt = new LightAmbient ( light_n, r, g, b );
                    }
                }

                if ( lt )
                    lights->addProperty ( lt );

                models->lights.push_back ( lights );
                i++;
            }
        }

        else if ( name.compare ( GROUP ) == 0 )
        {   Group *novo_group = new Group;
            group->children.push_back ( novo_group );
            readXMLFromRootElement ( element, models, novo_group );
        }
    }
}

Models *readXMLDoc ( const char *path )
{   XMLDocument doc;
    doc.LoadFile ( path );
    XMLElement *modelNode = doc.FirstChildElement ( SCENE );
    Models *models = new Models;
    models->n_buffers = 0;
    MatAmbient *mA = new MatAmbient();
    MatDiffuse *mD = new MatDiffuse();
    MatEmissive *mE = new MatEmissive();
    MatSpecular *mS = new MatSpecular();
    models->materials_defaults.push_back ( mA );
    models->materials_defaults.push_back ( mD );
    models->materials_defaults.push_back ( mE );
    models->materials_defaults.push_back ( mS );
    models->g = new Group;
    readXMLFromRootElement ( modelNode, models, models->g );
    return models;
}

void traverseTree ( Models *models, Group *group )
{   glPushMatrix();

    for ( auto transformation : group->transformations )
    {   transformation->applyTransformation();
    }

    drawElement ( models, group );

    for ( int i = 0; i < group->children.size(); i++ )
    {   traverseTree ( models, group->children[i] );
        glPopMatrix();
    }
}

