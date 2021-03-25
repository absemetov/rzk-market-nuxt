<template>
  <section>
    <h1>Users Page</h1>

    <ul>
      <li v-for="user of 5" :key="user">
        <NuxtLink :to="{ name: 'users-id', params: { id: user }}">User {{user}}</NuxtLink>
      </li>
    </ul>
  </section>
</template>
