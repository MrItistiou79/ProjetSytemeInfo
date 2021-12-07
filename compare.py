import matplotlib.pyplot as plt
import argparse


def parse():
    parser = argparse.ArgumentParser()
    parser.add_argument("-f", "--input-file-1", help="path to the csv file with the computed results with POSIX", type=str)
    parser.add_argument("-g", "--input-file-2", help="path to the csv file with the computed results with active waiting", type=str)
    parser.add_argument("-n", "--title", help="Title of the graph", type=str, default=None)
    return parser.parse_args()


def plot(filename_POSIX, filename_active, title):
    with open(filename_POSIX, 'r') as f:
        with open(filename_active, 'r') as g:
            lines_f = f.readlines()[1::]
            lines_g = g.readlines()[1::]
            data_moustache1 = []
            data_moustache2 = []
            nbr_threads = list(range(1, 9))
            av_time_1 = []
            av_time_2 = []
            for i in range(0, len(lines_f), 5):
                # moustache
                time1 = []
                time2 = []
                t1 = 0
                t2 = 0
                for j in range(5):
                    l1 = float(lines_f[i + j].strip().split(',')[1])
                    l2 = float(lines_g[i + j].strip().split(',')[1])
                    time1.append(l1)
                    time2.append(l2)
                    t1 += l1
                    t2 += l2
                av_time_1.append(t1 / 5)
                av_time_2.append(t2 / 5)
                data_moustache1.append(time1)
                data_moustache2.append(time2)

            fig, ax = plt.subplots(3, 1, figsize=(8, 10))

            ax[0].boxplot(data_moustache1)
            ax[0].set_xticklabels(nbr_threads)
            ax[0].set_ylabel("temps [s]", fontsize=12)
            ax[0].set_title("POSIX", fontsize=15)

            ax[1].boxplot(data_moustache2)
            ax[1].set_xticklabels(nbr_threads)
            ax[1].set_ylabel("temps [s]", fontsize=12)
            ax[1].set_title("Attente active", fontsize=15)

            ax[2].plot(nbr_threads, av_time_1, label = "POSIX")
            ax[2].plot(nbr_threads, av_time_2, label = "A-A")
            ax[2].legend()
            ax[2].set_ylabel("temps [s]", fontsize=12)
            ax[2].set_xlabel("Nombre de threads", fontsize=12)
            plt.xticks(nbr_threads, nbr_threads)
            ax[2].set_title(title, fontsize=15)
            plt.subplots_adjust(hspace=0.3)
            plt.savefig("plot_comparaison.png")

args = parse()
plot(args.input_file_1, args.input_file_2, args.title)


