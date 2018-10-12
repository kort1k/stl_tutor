#include <functional>
#include <iostream>
#include <string>
#include <set>
#include <unordered_set>

struct dev {
    std::string s;
    std::string e;
};

bool operator==(const dev& l, const dev& r) {
    return l.s == r.s && l.e == r.e;
}
bool operator<(const dev& l, const dev& r) {
  return l.s < r.s || (l.s <= r.s && l.e < r.e);
}

auto my_lambda_hash = [](auto &h1, auto &h2) {
  return h2 ^ (h1 << 1);
};

// function object for object 'dev'
struct dev_hash {
    std::size_t operator()(const dev &d) const noexcept
    {
        std::size_t h1 = std::hash<std::string>{}(d.s);
        std::size_t h2 = std::hash<std::string>{}(d.e);
        //std::size_t hr = h2 ^ (h1 << 1);
        
        return my_lambda_hash(h2, h2); // hr
    }
};

namespace std
{
  template<> struct hash<dev>
  {
    typedef dev argument_type;
    typedef size_t result_type;
    result_type operator()(const argument_type& d) const noexcept
    {
      result_type const h1 ( hash<string>{}(d.s) );
      result_type const h2 ( hash<string>{}(d.e) );
      return my_lambda_hash(h2, h2); // h2 ^ (h1 << 1);
    }
  };
} // namespace std

int main()
{
  dev d1 = {"aa", "cc"};
  dev d2 = {"ab", "bc"};
  dev d3 = {"aa", "aa"};
  std::set<dev> dev_sorted = {d1, d2, d3};
  std::unordered_set<dev> dev_unsorted = {d1, d2, d3};

  std::cout << "dev_hash(d1) = " << dev_hash{}(d1) << std::endl;
  std::cout << "hash(d1) =     " << std::hash<dev>{}(d1) << std::endl;

  for (auto s : dev_unsorted)
    std::cout << s.s << ' ' << s.e <<std::endl;

  for (auto s : dev_sorted)
    std::cout << s.s << ' ' << s.e <<std::endl;

  return 0;
}

