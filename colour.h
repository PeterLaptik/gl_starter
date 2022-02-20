#ifndef COLOUR_H
#define COLOUR_H


class Colour
{
    public:
        Colour(float r, float g, float b)
            : R(r), G(g), B(b)
        { }

        virtual ~Colour();


        float GetR(void) const
        {
            return R;
        }

        float GetG(void) const
        {
            return G;
        }

        float GetB(void) const
        {
            return B;
        }

    private:
        float R;
        float G;
        float B;
};

#endif // COLOUR_H
