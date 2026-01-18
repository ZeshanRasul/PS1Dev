#include "track.h"

#define BYTES_PER_VERTEX    16
#define BYTES_PER_FACE      20
#define BYTES_PER_SECTION   156

void LoadTrackVertices(Track *track, char *filename)
{
    u_long i;
    u_long b;
    u_long length;
    u_char *bytes;

    bytes = (u_char*) FileRead(filename, &length);

    if (bytes == NULL)
    {
        printf("Error reading %s from the CD.\n", filename);
        return;
    }

    b = 0;

    track->numvertices = length / BYTES_PER_VERTEX;
    track->vertices = (VECTOR*) malloc(track->numvertices * sizeof(VECTOR));

    for (i = 0; i < track->numvertices; i++)
    {
        track->vertices[i].vx = GetLongBE(bytes, &b);
        track->vertices[i].vy = GetLongBE(bytes, &b);
        track->vertices[i].vz = GetLongBE(bytes, &b);
        track->vertices[i].pad = GetLongBE(bytes, &b);
    }

    free(bytes);
}

void LoadTrackFaces(Track *track, char *filename)
{
    u_long i;
    u_long b;
    u_long length;
    u_char *bytes;

    bytes = (u_char*) FileRead(filename, &length);

    if (bytes == NULL)
    {
        printf("Error reading %s from the CD.\n", filename);
        return;
    }

    b = 0;

    track->numfaces = length / BYTES_PER_FACE;
    track->faces = (Face*) malloc(track->numfaces * sizeof(Face));

    for (i = 0; i < track->numfaces; i++)
    {
        Face *face = &track->faces[i];
        face->indices[0] = GetShortBE(bytes, &b);
        face->indices[1] = GetShortBE(bytes, &b);
        face->indices[2] = GetShortBE(bytes, &b);
        face->indices[3] = GetShortBE(bytes, &b);

        face->normal.vx = GetShortBE(bytes, &b);
        face->normal.vy = GetShortBE(bytes, &b);
        face->normal.vz = GetShortBE(bytes, &b);

        face->texture = GetChar(bytes, &b);

        face->flags = GetChar(bytes, &b);

        face->color.r = GetChar(bytes, &b);
        face->color.g = GetChar(bytes, &b);
        face->color.b = GetChar(bytes, &b);
        face->color.cd = GetChar(bytes, &b);
    }
    free(bytes);
}

void LoadTrackSections(Track *track, char *filename)
{
    u_long i;
    u_long b;
    u_long length;
    u_char *bytes;

    bytes = (u_char*) FileRead(filename, &length);

    if (bytes == NULL)
    {
        printf("Error reading %s from the CD.\n", filename);
        return;
    }

    b = 0;

    track->numsections = length / BYTES_PER_SECTION;
    track->sections = (Section*) malloc(track->numsections * sizeof(Section));

    for (i = 0; i < track->numsections; i++)
    {
        b += 4;

        track->sections[i].prev = track->sections + GetLongBE(bytes, &b);
        track->sections[i].next = track->sections + GetLongBE(bytes, &b);

        track->sections[i].center.vx = GetLongBE(bytes, &b);
        track->sections[i].center.vy = GetLongBE(bytes, &b);
        track->sections[i].center.vz = GetLongBE(bytes, &b);

        b += 118;

        track->sections[i].facestart = GetShortBE(bytes, &b);
        track->sections[i].numfaces = GetShortBE(bytes, &b);

        b += 4;

        track->sections[i].flags = GetShortBE(bytes, &b);
        track->sections[i].id = GetShortBE(bytes, &b);
        track->sections[i].id = i;

        b += 2;
    }
    free(bytes);
}
