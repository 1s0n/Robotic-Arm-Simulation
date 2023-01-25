class GameObject
{
    public:
        GameObject();
        ~GameObject();

        bool hasCollided(GameObject other);


        int hitboxWidth;
        int hitboxHeight;

    protected:
        bool isVisible;
        
        int x;
        int y;

        double rotation;
};