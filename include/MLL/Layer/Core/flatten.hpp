#ifndef _MLL_LAYER_CORE_FLATTEN_HPP
#define _MLL_LAYER_CORE_FLATTEN_HPP

namespace MLL{
    class Flatten : public CoreLayer{
    private:

    public:
        Flatten();

        void compile();

        void forward_propagation(const Layer&);
        void back_propagation(const Layer&);

        Layer* copy() const { return new Flatten(*this); }    
    };
}

#endif//_MLL_LAYER_CORE_FLATTEN_HPP
