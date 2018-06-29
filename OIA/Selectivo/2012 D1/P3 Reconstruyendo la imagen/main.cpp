#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long int lli;
const lli MAX_RECT = 22;
const lli dirs[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };

struct Point {
	lli x, y;
	
	bool operator<(const Point& other) const {
		if(x == other.x)
			return y < other.y;
		else
			return x < other.x;
	}
	
	bool operator==(const Point& other) const {
		return x == other.x && y == other.y;
	}
};
struct Rectangle {
	Point a, b;
	
	bool operator<(const Rectangle& other) const {
		if(a == other.a)
			return b < other.b;
		else
			return a < other.a;
	}
	
	bool operator==(const Rectangle& other) const {
		return a == other.a && b == other.b;
	}
};
struct Query {
	Rectangle rect;
	Point start;
	
	bool operator<(const Query& other) const {
		if(rect == other.rect)
			return start < other.start;
		else
			return rect < other.rect;
	}
};

std::ostream &operator<<(std::ostream &os, const Point& p) { 
    return os << "{ " << p.x << ", " << p.y << " }";
}
std::ostream &operator<<(std::ostream &os, const Rectangle& r) { 
    return os << "{ " << r.a << ", " << r.b << " }";
}

bool intersection(Rectangle a, Rectangle b, Rectangle& result){
	result.a.x = max(a.a.x, b.a.x);
	result.a.y = max(a.a.y, b.a.y);
	
	result.b.x = min(b.b.x, a.b.x);
	result.b.y = min(b.b.y, a.b.y);
	
	return result.b.x > result.a.x &&
		   result.b.y > result.a.y;
}

int N;
vector<Rectangle> rectangles;
int grid[MAX_RECT][MAX_RECT];

lli query(Query& query){
	cout << query.rect << ", Starting at: " << query.start << endl;
	
	// clear grid
	for(int i = 0; i < MAX_RECT; i++)
		for(int j = 0; j < MAX_RECT; j++)
			grid[i][j] = 0;
			
	// fill grid
	for(Rectangle& r : rectangles){
		Rectangle fill_rect;
		if(intersection(query.rect, r, fill_rect)){
			cout << "int" << endl;
			for(lli i = fill_rect.a.x; i < fill_rect.b.x; i++)
				for(lli j = fill_rect.a.y; j < fill_rect.b.y; j++)
					grid[j - fill_rect.a.y][i - fill_rect.a.x]++;
		}
	}
	
	
	for(int i = 0; i < MAX_RECT; i++){
		for(int j = 0; j < MAX_RECT; j++){
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
		cout << endl;
		cout << endl;
	
	// bfs
	queue<Point> q;
	while(!q.empty()){
		Point p = q.front();
		q.pop();
		
		for(int i = 0; i < 4; i++){
			Point pp = { p.x + dirs[i][0], p.y + dirs[i][1] };
		}
	}
	
	return 0;
}

int main() {
	ifstream cin("agujeros.in");
#ifndef LOCAL
	ofstream cout("agujeros.out");
#endif
	
	cin >> N;
	rectangles.resize(N);
	
	for(int i = 0; i < N; i++){
		Rectangle& rect = rectangles[i];
		cin >> rect.a.x >> rect.a.y >> rect.b.x >> rect.b.y;
	}

	vector<Query> queries;

	for(int i = 0; i < N; i++){
		for(int j = i + 1; j < N; j++){
			Rectangle result;
			if(intersection(rectangles[i], rectangles[j], result)){
				//cout << "Intersection between " << (i + 1) << " and " << (j + 1) << " at " << result << endl;
				
				Point bottom_left = result.a;
				
				queries.push_back(Query { Rectangle { { bottom_left.x - MAX_RECT, bottom_left.y - MAX_RECT }, bottom_left }, { bottom_left.x - 1, bottom_left.y - 1 }});
				/*
				queries.push_back(Point { result.b.x, result.b.y });
				
				queries.push_back(Point { result.a.x - 1, result.b.y });
				queries.push_back(Point { result.b.x, result.a.y - 1 });
				*/
			}
		}
	}
	
	vector<lli> areas;
	
	for(Query q : queries){
		lli area = query(q);
		if(area != 0) areas.push_back(area);
	}
	
	sort(areas.begin(), areas.end());
	
	cout << areas.size() << "\n";
	for(lli area : areas) cout << area << "\n";
	
	system("pause");
	
	return 0;
}
