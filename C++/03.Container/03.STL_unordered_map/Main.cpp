#include "../global.h"

struct GameCharacter
{

private:
	int code;
	int level;
	int money;

public:
	const int Code()const
	{return code;}
	const int Level()const
	{return level;}
	const int Money()const
	{return money;}

public:
	friend std::ostream& operator<<(std::ostream& os, const GameCharacter& other)
	{
		return os << "캐릭터 코드 : " << other.code << ", 레벨 : " << other.level << ", 돈 : " << other.money << std::endl;
	}
public:
	GameCharacter() = default;
	GameCharacter(int code, int level, int money) :code(code), level(level), money(money) {}
	GameCharacter(const GameCharacter& other) { code = other.Code(); level = other.Level(); money = other.Money();};
	~GameCharacter() {};
};




int main()
{
	std::unordered_map<int, GameCharacter> characters;

	GameCharacter character1(1, 10, 100);
	GameCharacter character2(2, 20, 200);
	GameCharacter character3(3, 30, 300);
	GameCharacter character4(4, 40, 400);
	GameCharacter character5(5, 50, 500);

	characters.insert(std::pair<int, GameCharacter>(character1.Code(), character1));
	characters.insert(std::pair<int, GameCharacter>(character2.Code(), character2));
	characters.insert(std::pair<int, GameCharacter>(character3.Code(), character3));
	characters.insert(std::pair<int, GameCharacter>(character4.Code(), character4));
	characters.insert(std::pair<int, GameCharacter>(character5.Code(), character5));

	cout << "=============== 캐릭터 추가 ===============" << endl;

	for (auto& iter : characters)
		cout << iter.second << endl;

	Pause;
	Clean;

	cout << "=============== 캐릭터 삭제 ===============" << endl;
	characters.erase(3);
	
	for (auto& iter : characters)
		cout << iter.second << endl;

	Pause;
	Clean;

}