Import('env')

env.Append(CPPPATH=[Dir('.')])

env.add_sources([
])

if env.get_platform() == 'omnet':
    if env.conf.bool('mixim'):
        SConscript('MiXiM/SConscript')

if env.get_platform() == 'local' or env.get_platform() == 'python':
    SConscript('rs232/SConscript')

if env.conf.bool('fnet') or (env.conf.str('platform') == 'frdm_k64f' and (env.conf.bool('pal_firmware') or env.conf.bool('pal_pers'))): # pal_firmware and pal_pers need the flash driver of fnet
    SConscript("fnet/fnet_stack/SConscript")
