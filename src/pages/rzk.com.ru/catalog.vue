<template>
  <div class="container">
    <div>
      <h1 class="title">
        Catalog
        <NuxtLink to="/">Home page</NuxtLink>
      </h1>
      <ul>
        <li v-for="currency of currencies" :key="currency.id">
          <h1>{{ currency.id }} {{ currency.rateBuy }} / {{ currency.rateSell }}</h1>
        </li>
      </ul>
    </div>
  </div>
</template>

<script>
export default {
  async asyncData({ params, $http, $fire }) {
    //const users = await $http.$get(`https://jsonplaceholder.typicode.com/users`);
    const snapshot = await $fire.firestore.collection('currencies').get();
    const currencies = snapshot.docs.map( doc => {
      return {id: doc.id, ...doc.data()}
    });
    return { currencies }
  },
  head: {
    title: 'RZK Market 2.0 Catalog'
  },
  httpHeaders: () => ({
    'Cache-Control': 'public, max-age=300, s-maxage=600'
  })
};
</script>
