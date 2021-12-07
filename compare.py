import matplotlib.pyplot as plt
import argparse


def parse():
    parser = argparse.ArgumentParser()
    parser.add_argument("-a", "--check", help="check if 2 of 3 files", type=int)
    parser.add_argument("-f", "--input-file-1", help="path to the csv file with the computed results with POSIX",
                        type=str)
    parser.add_argument("-g", "--input-file-2", help="path to the csv file with the computed results with TAS",
                        type=str)
    parser.add_argument("-h", "--input-file-3", help="path to the csv file with the computed results with TATAS",
                        type=str)
    parser.add_argument("-n", "--title", help="Title of the graph", type=str, default=None)
    return parser.parse_args()


def plot3(filename_POSIX, filename_TAS, filename_TATAS, title):
    with open(filename_POSIX, 'r') as f:
        with open(filename_TAS, 'r') as g:
            with open(filename_TATAS, 'r') as h:
                lines_f = f.readlines()[1::]
                lines_g = g.readlines()[1::]
                lines_h = h.readline()[1::]

                nbr_threads = list(range(1, 9))  # number of threads

                av_time_1 = []  # average time for POSIX locks and semaphores
                av_time_2 = []  # average time for TAS locks and semaphores
                av_time_3 = []  # average time for TATAS locks and semaphores
                for i in range(0, len(lines_f), 5):
                    t1 = 0
                    t2 = 0
                    t3 = 0
                    for j in range(5):  # incrementing average times
                        t1 += float(lines_f[i + j].strip().split(',')[1])
                        t2 += float(lines_g[i + j].strip().split(',')[1])
                        t3 += float(lines_h[i + j].strip().split(',')[1])
                    av_time_1.append(t1 / 5)
                    av_time_2.append(t2 / 5)
                    av_time_3.append(t3 / 5)

                # Plotting
                plt.plot(nbr_threads, av_time_1, label="POSIX")
                plt.plot(nbr_threads, av_time_2, label="TAS")
                plt.plot(nbr_threads, av_time_3, label="TATAS")
                plt.xticks(nbr_threads, nbr_threads)
                plt.grid(True)
                plt.title(title)

                plt.savefig("comparaison.png")


def plot2(filename_TAS, filename_TATAS, title):
    with open(filename_TAS, 'r') as f:
        with open(filename_TATAS, 'r') as g:
            lines_f = f.readlines()[1::]
            lines_g = g.readlines()[1::]

            nbr_threads = list(range(1, 9))  # number of threads

            av_time_1 = []  # average time for TAS locks testing
            av_time_2 = []  # average time for TATAS locks testing
            for i in range(0, len(lines_f), 5):
                t1 = 0
                t2 = 0
                for j in range(5):  # incrementing average times
                    t1 += float(lines_f[i + j].strip().split(',')[1])
                    t2 += float(lines_g[i + j].strip().split(',')[1])
                av_time_1.append(t1 / 5)
                av_time_2.append(t2 / 5)

            # Plotting
            plt.plot(nbr_threads, av_time_1, label="TAS")
            plt.plot(nbr_threads, av_time_2, label="TATAS")
            plt.xticks(nbr_threads, nbr_threads)
            plt.grid(True)
            plt.title(title)

            plt.savefig("comparaison.png")


args = parse()
if args.check == 2:
    plot2(args.args.input_file_1, args.input_file_2, args.title)
else:
    plot3(args.input_file_1, args.input_file_2, args.input_file_3, args.title)
