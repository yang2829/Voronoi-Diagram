import _fortune
import numpy as np
import matplotlib.pyplot as plt

def main():
    g1 = _fortune.Fortune(10)
    g1.RunAlgo()
    points = g1.get_points()
    edges = g1.get_edges()
    x = []
    y = []
    for p in points:
        print(p.point)
        x.append(p.point[0])
        y.append(p.point[1])
    plt.scatter(x, y, c='r', marker='o')
    count = 0
    for e in edges:
        print(e.s, "-->", e.d)
        if (e.s_finish and e.d_finish):
            print("draw edge")
            count += 1
            plt.plot([e.s[0], e.d[0]], [e.s[1], e.d[1]], 'r', lw=1)

    print("npoint: ", len(points), " nedge: ", len(edges), " draw edge: ", count)

    llim = 0
    rlim = 500
    step = 100
    plt.xlim((llim,rlim))
    plt.ylim((llim,rlim))
    plt.xticks(np.arange(llim,rlim,50))
    plt.yticks(np.arange(llim,rlim,50))
    plt.show()


if __name__ == '__main__':
    main()