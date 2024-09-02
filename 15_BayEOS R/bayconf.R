library(bayeos)

# TODO:Please change
bayeos.connect("https://bayeos.bayceer.uni-bayreuth.de/BayEOS-Server/XMLServlet",
    user = "workshop", password = "workshop", save_as = "workshop"
)

bayeos.connect("workshop")
bayeos.ls()
bayeos.cd(138398)

d <- bayeos.getSeries(c(138399, 138400))
plot(d)
