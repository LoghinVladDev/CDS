//
// Created by loghin on 07.03.2021.
//

#ifndef CDS_GENERATOR_HPP
#define CDS_GENERATOR_HPP


template <class T>
class Generator: public Object {

};

/**
 * class IntGenerator : public Generator<int> {
 * public:
 *      auto task () noexcept {
 *          int i = 1;
 *          while ( true ) {
 *              this->yield(i++);
 *          }
 *      }
 *
 *
 * };
 */

#endif //CDS_GENERATOR_HPP
