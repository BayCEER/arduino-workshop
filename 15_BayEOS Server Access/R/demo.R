library(bayeos)
bayeos.connect('http://bayeos.bayceer.uni-bayreuth.de/BayEOS-Server/XMLServlet','gast','gast')
## We can use IDs to navigate or to get data
bayeos.cd()
bayeos.cd(36076)
data=bayeos.getSeries(c(2717,2718))
plot(data)

## Alternatively one can use names
bayeos.cd()
bayeos.cd('Micrometeorology Dept/AWS Ecological Botanical Garden/AWS EBG Data start May 08, 1997')
data=bayeos.getSeries('Lufttemperatur & Feuchte/Lufttemperatur 02 m Höhe (HMP45)')
plot(data)

## Using interval
data=bayeos.getSeries(2718,interval='last month')
plot(data)

## Using from and until
data=bayeos.getSeries(2718,from='2017-01-01',until='2017-02-01')
plot(data)

## Fetching pre-aggregated data
data=bayeos.getSeries(2718,from='2010-01-01',aggfunc='avg',aggint='day')
plot(data)

## Using zoo and xts to make weekly aggregates
library(zoo)
library(xts)
plot(apply.weekly(data,mean))

bayeos.close()
