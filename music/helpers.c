// Helper functions for music

#include <cs50.h>
#include <math.h>
#include<stdio.h>

#include "helpers.h"


// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    return (fraction[0] - '0') * 8 / (fraction[2] - '0');
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    // TODO
    int semitones;
    if (note[0] == 'A')
    {
        if (note[1] == '#')
        {
            semitones = 0 + 12 * (note[2] - '0' - 4) + 1;
        }
        if (note[1] == 'b')
        {
            semitones = 0 + 12 * (note[2] - '0' - 4) - 1;
        }
        else if (note[1] != '#' && note[1] != 'b')
        {
           semitones = 0 + 12 * (note[1] - '0' - 4);
        }
    }
    if (note[0] == 'B')
    {
        if (note[1] == '#')
        {
            semitones = 2 + 12 * (note[2] - '0' - 4) + 1;
        }
        if (note[1] == 'b')
        {
            semitones = 2 + 12 * (note[2] - '0' - 4) - 1;
        }
        else if (note[1] != '#' && note[1] != 'b')
        {
           semitones = 2 + 12 * (note[1] - '0' - 4);
        }
    }
    if (note[0] == 'C')
    {
        if (note[1] == '#')
        {
            semitones = -9 + 12 * (note[2] - '0' - 4) + 1;
        }
        if (note[1] == 'b')
        {
            semitones = -9 + 12 * (note[2] - '0' - 4) - 1;
        }
        else if (note[1] != '#' && note[1] != 'b')
        {
           semitones = -9 + 12 * (note[1] - '0' - 4);
        }
    }
    if (note[0] == 'D')
    {
        if (note[1] == '#')
        {
            semitones = -7 + 12 * (note[2] - '0' - 4) + 1;
        }
        if (note[1] == 'b')
        {
            semitones = -7 + 12 * (note[2] - '0' - 4) - 1;
        }
        else if (note[1] != '#' && note[1] != 'b')
        {
           semitones = -7 + 12 * (note[1] - '0' - 4);
        }
    }
    if (note[0] == 'E')
    {
        if (note[1] == '#')
        {
            semitones = -5 + 12 * (note[2] - '0' - 4) + 1;
        }
        if (note[1] == 'b')
        {
            semitones = -5 + 12 * (note[2] - '0' - 4) - 1;
        }
        else if (note[1] != '#' && note[1] != 'b')
        {
           semitones = -5 + 12 * (note[1] - '0' - 4);
        }
    }
    if (note[0] == 'F')
    {
        if (note[1] == '#')
        {
            semitones = -4 + 12 * (note[2] - '0' - 4) + 1;
        }
        if (note[1] == 'b')
        {
            semitones = -4 + 12 * (note[2] - '0' - 4) - 1;
        }
        else if (note[1] != '#' && note[1] != 'b')
        {
           semitones = -4 + 12 * (note[1] - '0' - 4);
        }
    }
    if (note[0] == 'G')
    {
        if (note[1] == '#')
        {
            semitones = -2 + 12 * (note[2] - '0' - 4) + 1;
        }
        if (note[1] == 'b')
        {
            semitones = -2 + 12 * (note[2] - '0' - 4) - 1;
        }
        else if (note[1] != '#' && note[1] != 'b')
        {
           semitones = -2 + 12 * (note[1] - '0' - 4);
        }
    }
    return round(440.0 * pow(2.0, semitones/12.0));
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    // TODO
    if (s[0] == '\0')
    {
        return true;
    }
    else
    {
        return false;
    }
}
