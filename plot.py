import matplotlib.pyplot as plt
import argparse

def parse():
	parser = argparse.ArgumentParser()
	parser.add_argument("-f", "--input-file", help="path to the csv file with the computed results", type=str)
	parser.add_argument("-n", "--title",  help="Title of the graph", type=str, default=None)
	return parser.parse_args()

def plot(filename, title):
	with open(filename, 'r') as f :
		lines = f.readlines()[1::]
		data_moustache = []
		names_moustache = []

		nbr_threads = list(range(1,9))
		av_time = []
		for i in range(0, len(lines), 5):
			#moustache
			time = []
			names_moustache.append(lines[i].strip().split(',')[0])

			#pas moustache
			t = 0

			for j in range(5):
				l = float(lines[i+j].strip().split(',')[1])
				time.append(l)
				t += l
			av_time.append(t/5)
			data_moustache.append(time)

		fig, ax = plt.subplots(2,1, figsize=(8,10))

		ax[0].boxplot(data_moustache)
		ax[0].set_xticklabels(names_moustache)
		ax[0].set_ylabel("temps [s]", fontsize=12)
		ax[0].set_xlabel("Nombre de threads", fontsize=12)
		ax[0].set_title(title, fontsize=15)

		ax[1].plot(nbr_threads, av_time)
		ax[1].set_ylabel("temps [s]", fontsize=12)
		ax[1].set_xlabel("Nombre de threads", fontsize=12)
		plt.xticks(nbr_threads, nbr_threads)
		ax[1].set_title(title, fontsize=15)
		plt.subplots_adjust(hspace=0.3)
		plt.savefig("plot.png")

args = parse()
plot(args.input_file, args.title)
	
	
