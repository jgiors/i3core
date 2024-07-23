#ifndef I3PRNG_H
#define I3PRNG_H
///@file

#include <cstdint>
#include <vector>

namespace i3 {
    namespace core {
        ///32-bit pseudorandom number generator of type xorshift128 (128-bit state).
        ///Algorithm "xor128" from p. 5 of Marsaglia, "Xorshift RNGs"
        class Prng {
        public:
            using std::uint32_t;

            ///Internal PRNG state.
            struct State {
                uint32_t a, b, c, d;
            };

        private:
            State _state;

        public:
            Prng() = delete;

            ///Create a Prng, using the hash of a seed buffer to initialize.
            Prng(const std::vector<uint8_t> &seed);

            ///Create a Prng with the provided state.
            Prng(State state) : _state{state} {}

            ///Get a random unsigned 32-bit value.       
            uint32_t random32();

            ///Typical rand function. Returns a value between 0 and n-1 inclusive (or 0 when n == 0).
            uint32_t random(uint32_t n);

            ///Rand function which returns value between 0 and n inclusive.
            uint32_t random0toN(uint32_t n);

            ///Pick a random integer in the range [i, j].
            int32_t randomRange(int32_t i, int32_t j);

            ///Return a random double precision float between 0 and 1 inclusive.
            double RandomReal();

            ///Splits the random generator and advances the original one step.
            Prng split();

            ///Splits the random generator, but does not advance the state of the original generator.
            ///@important   Do not split the same generator twice without advancing it,
            ///             otherwise the new generators will be identical and correlated.
            Prng split_noMutate() const;

            ///Split the random generator, including the hash of the supplied parameters buffer
            ///in the splitting process.
            ///@note Do not use a long parameters buffer. It is copied within this function.
            Prgn split_parameterized(const std::vector<uint8_t> &parameters) const;

            ///Get the internal state.
            State state() const { return _state; }
        };
    } //namespace core
} //namespace i3

#endif //I3PRNG_H
