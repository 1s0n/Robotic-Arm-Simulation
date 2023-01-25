class Camera
{
    public:
        Camera();
        ~Camera();

        void GetRelativePosition(int xin, int yin, int* xout, int* yout);

        void SetPos(int x, int y);
        void MoveIP(int x, int y);

    private:
        int x;
        int y;

        int width = 800;
        int height = 600;
};