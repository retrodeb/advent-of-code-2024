

namespace aoc {

struct Block {
	enum class Type {
		Empty,
		Obstacle
	} type;
	
	Block(Type type) : type{type} {}
};

}
