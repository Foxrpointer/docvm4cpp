// 单例类

class Render
{
    private:
    ~Render();
    static Render* getInstance();

    public:
    static Render* self;
    Render();
};