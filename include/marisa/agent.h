#ifndef MARISA_AGENT_H_
#define MARISA_AGENT_H_

#include <memory>

#if __cplusplus >= 201703L
 #include <string_view>
#endif  // __cplusplus >= 201703L

#include "marisa/key.h"
#include "marisa/query.h"

namespace marisa {
namespace grimoire {
namespace trie {

class State;

}  // namespace trie
}  // namespace grimoire

class Agent {
 public:
  Agent();
  ~Agent();

  const Query &query() const {
    return query_;
  }
  const Key &key() const {
    return key_;
  }

#if __cplusplus >= 201703L
  void set_query(std::string_view str) {
    set_query(str.data(), str.length());
  }
#endif  // __cplusplus >= 201703L
  void set_query(const char *str);
  void set_query(const char *ptr, std::size_t length);
  void set_query(std::size_t key_id);

  const grimoire::trie::State &state() const {
    return *state_;
  }
  grimoire::trie::State &state() {
    return *state_;
  }

#if __cplusplus >= 201703L
  void set_key(std::string_view str) {
    set_key(str.data(), str.length());
  }
#endif  // __cplusplus >= 201703L
  void set_key(const char *str) {
    MARISA_DEBUG_IF(str == NULL, MARISA_NULL_ERROR);
    key_.set_str(str);
  }
  void set_key(const char *ptr, std::size_t length) {
    MARISA_DEBUG_IF((ptr == NULL) && (length != 0), MARISA_NULL_ERROR);
    MARISA_DEBUG_IF(length > MARISA_UINT32_MAX, MARISA_SIZE_ERROR);
    key_.set_str(ptr, length);
  }
  void set_key(std::size_t id) {
    MARISA_DEBUG_IF(id > MARISA_UINT32_MAX, MARISA_SIZE_ERROR);
    key_.set_id(id);
  }

  bool has_state() const {
    return state_.get() != NULL;
  }
  void init_state();

  void clear();
  void swap(Agent &rhs);

 private:
  Query query_;
  Key key_;
  std::unique_ptr<grimoire::trie::State> state_;

  // Disallows copy and assignment.
  Agent(const Agent &);
  Agent &operator=(const Agent &);
};

}  // namespace marisa

#endif  // MARISA_AGENT_H_
