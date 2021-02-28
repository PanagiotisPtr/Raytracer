#ifndef PRIMITIVES_REFERENCECONTAINER_H
#define PRIMITIVES_REFERENCECONTAINER_H

#include <unordered_set>
#include <stack>
#include <functional>
#include <iterator>

namespace primitives {

/**
 * This container has the following properties
 *
 * Space Complexity O(2N) - amortised
 * Lookup O(1)
 * getLast O(1)
 * Delete O(1)
 * insert O(1)
 */
template<typename ObjectClass>
class ReferenceContainer {
public:
    using constObjectReference = std::reference_wrapper<const ObjectClass>;
    
    ReferenceContainer() {}

    struct ConstReferenceHash {
        size_t operator() (const constObjectReference& r) const {
            return std::hash<const void*>{}((const void*)&r.get());
        }
    };

    struct ConstReferenceCompare {
        bool operator()(const constObjectReference& a, const constObjectReference& b) const {
            return &a.get() == &b.get();
        }
    };

    void add(const ObjectClass& reference) {
        this->references.insert(std::cref(reference));
        this->stack.push(std::cref(reference));
    }

    void remove(const ObjectClass& reference) {
        if (this->contains(reference)) {
            this->references.erase(reference);
        }
    }

    bool contains(const ObjectClass& reference) {
        return this->references.find(reference) != std::end(this->references);
    }

    bool size() { return this->references.size(); }

    const ObjectClass& getLast() {
        while (!this->stack.empty() && !this->contains(this->stack.top().get())) {
            this->stack.pop();
        }

        return this->stack.top().get();
    }

    const std::unordered_set<constObjectReference> getReferences() const { return this->references; }

    typename std::unordered_set<constObjectReference, ConstReferenceHash>::iterator end() { return std::end(this->references); }

    typename std::unordered_set<constObjectReference, ConstReferenceHash>::iterator begin() { return std::begin(this->references); }
private:
    std::unordered_set<constObjectReference, ConstReferenceHash, ConstReferenceCompare> references;
    std::stack<constObjectReference> stack;
};

} // namespace primitives

#endif