#ifndef _MLL_LAYER_CORE_INPUT_HPP
#define _MLL_LAYER_CORE_INPUT_HPP

namespace MLL{
    class Input : public CoreLayer{
    private:

    public:
        Input(int);

        void compile();

        void forward_propagation(const Layer&);
        void back_propagation(const Layer&);

        Layer* copy() const { return new Input(*this); }
    };
}

#endif//_MLL_LAYER_CORE_INPUT_HPP
