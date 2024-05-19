class Coordenada {
    public:
        Coordenada() {
            x = 0;
            y = 0;
        }

        Coordenada(int _x, int _y) {
            x = _x;
            y = _y;
        }

        int getX() const {
        return x;
        }

        int getY() const {
            return y;
        }
    
    private:
        int x;
        int y;
};