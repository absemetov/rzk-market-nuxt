<template>
  <div>
    <NuxtLink to="/rzk.com.ru">rzk.com.ru</NuxtLink>
    <NuxtLink to="/absemetov.org.ua">absemetov.org.ua</NuxtLink>
    <NuxtLink to="/nilson.com.ua">nilson.com.ua</NuxtLink>
    <NuxtLink to="/nilson.com.ua/catalog">nilson.com.ua/catalog</NuxtLink>
  </div>
</template>

<script>
export default {
  head: {
    title: 'RZK Market 2.0',
    meta: [
      { charset: 'utf-8' },
      { name: 'viewport', content: 'width=device-width, initial-scale=1' },
      {
        hid: 'description',
        name: 'description',
        content: 'my website description'
      }
    ],
    link: [{ rel: 'icon', type: 'image/x-icon', href: '/favicons/rzk.com.ua.ico' }]
  }
}
</script>
